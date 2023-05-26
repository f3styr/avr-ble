#include <drivers/bluetooth/ble.h>
#include "rn487x.h"
#include <errno.h>

#define PRINT_DEBUG_MSG

#define RN487X_RX_BUFF_SIZE  256
#define RN487X_RX_BUFF_MASK (RN487X_RX_BUFF_SIZE - 1)

#define RN487X_CMD_BUFF_SIZE 256


#define RN487X_USB_CDC_BUFF_SIZE 128

#define RN487X_RESET_DELAY (10)
#define RN487X_STARTUP_TIME (300)
#define RN487X_DELAY_WAIT_FOR_RESPONSE (300)

#define RN487X_MAX_SUPPORTED_PRIVATE_SERVICES (4)
#define RN487X_MAX_SUPPORTED_CHARACTERISTICS_PER_SERVICE (8)

#define RN487X_TEMP_AND_HUM_SERVICE_UUID "2A981F4C744841F883E88BF97FE46381"
#define RN487X_TEMP_READ_CHARACTERISTIC_UUID "73657BD82D044C31A31E54DE1DAB66FF"
#define RN487X_HUM_READ_CHARACTERISTIC_UUID "D0A512D60D8145C2BEDD621EF1CBBEFB"


#define RN487X_RESPONSE_NEW_CONNECTION "%CONNECT,"
#define RN487X_RESPONSE_CONNECTION_SECURED "%SECURED%"
#define RN487x_RESPONSE_DISCONNECT "%DISCONNECT%"
#define RN487x_RESPONSE_BONDED	"%BONDED%"
#define RN487x_RESPONSE_RECIEVE_NOTIFICATION	"%WC,"
#define RN487x_RESPONSE_RECIEVE_WRITE_REQUEST	"%WV,"

#define RN487X_RESPONSE_ERR "Err"
#define RN487X_RESPONSE_SUCC "AOK"

#define MAC_ADDRESS_BYTE_LEN 6

static volatile uint8_t rn487x_rx_buff[RN487X_RX_BUFF_SIZE];
static volatile size_t rx_wptr = 0;

static volatile uint8_t rn487x_usb_rx_buff[RN487X_USB_CDC_BUFF_SIZE];
static volatile size_t usb_rx_wptr = 0;

static volatile uint8_t rn487x_cmd_buff_a[RN487X_CMD_BUFF_SIZE];
static volatile uint8_t rn487x_cmd_buff_b[RN487X_CMD_BUFF_SIZE];

static struct ble_events rn487x_events;
static struct ble_sys_ops rn487x_sys_ops;
static struct ble_gatt_ops rn487x_gatt_ops;
static struct ble_gap_ops rn487x_gap_ops;

static void rn487x_clear_rx_buff(void);

static void rn487x_probe(void);
static void rn487x_cb_isr(void);
static void rn487x_usb_cdc_isr(void);
static void rn487x_main_loop(struct ble_server*);
static void rn487x_rx_strstr(uint8_t* str);

ble_error_t rn487x_init(struct ble_server*);

ble_error_t rn487x_read_handle(uint8_t, uint8_t, uint8_t*);
ble_error_t rn487x_write_handle(uint8_t, uint8_t, const uint8_t*);

ble_error_t rn487x_gatt_init(struct ble_server* ctx);
ble_error_t rn487x_register_service(struct gatt_service*);
ble_error_t rn487x_register_characteristic(struct gatt_characteristic*);
ble_error_t rn487x_gatt_init(struct ble_server*);

ble_error_t rn487x_gap_init(struct ble_server* ctx);
ble_error_t rn487x_set_address(struct ble_server* ctx, const uint8_t*);
ble_error_t rn487x_set_device_name(struct ble_server*, const uint8_t*);
ble_error_t rn487x_set_appearance(struct ble_server* ctx, const ble_gap_appearance_t);
ble_error_t rn487x_set_connection_params(struct ble_server*,
												const uint16_t,
												const uint16_t,
												const uint16_t,
												const uint16_t);

static ble_error_t rn487x_get_err_from_response();

static struct gatt_service *rn487x_services[] = {&temp_and_hum_service};

static struct gatt_characteristic *temp_and_hum_characteristics[] = 
	{&temp_read_characteristic, &humidity_read_characteristic};

struct gatt_characteristic temp_read_characteristic = {
	.UUID = RN487X_TEMP_READ_CHARACTERISTIC_UUID,
	.properties = BLE_PROP_FLAG_READ | BLE_PROP_FLAG_NOTIFY,
	.data_len = 10,
};

struct gatt_characteristic humidity_read_characteristic = {
	.UUID = RN487X_HUM_READ_CHARACTERISTIC_UUID,
	.properties = BLE_PROP_FLAG_READ | BLE_PROP_FLAG_NOTIFY,
	.data_len = 10,	
};

struct gatt_service temp_and_hum_service = {
	.UUID = "2A981F4C744841F883E88BF97FE46381",
	.characteristics = &temp_and_hum_characteristics,
	.characteristics_count = 2,
};

struct ble_server_config rn487x_config = {
	.device_name = "rn4870",
	.io_capabilities = IO_CAPS_KEYBOARD_DISPLAY,
	.passkey = "123456",
	.advertisement_appearance = BLE_APPEARANCE_UNKNOWN,
	.connection_min_interval = 0x0006,
	.connection_max_interval = 0x0000,
	.connection_latency = 0x0200,
	.connection_timeout = 0x0000,
	.services_count = 1,
	.services = &rn487x_services
};

static struct ble_events rn487x_events = {
};

struct ble_server rn487x = {

	.config = &rn487x_config,
	.sys = &rn487x_sys_ops,
	.gatt = &rn487x_gatt_ops,
	.gap = &rn487x_gap_ops,
	.events = &rn487x_events,

	.init = rn487x_init,
	.main_loop = rn487x_main_loop,
	//.probe = rn487x_probe,
	
};

static void rn487x_parse_responses(struct ble_server* ctx)
{

	if(ctx->events->cb_on_new_connection && 
		strstr(rn487x_get_response(), RN487X_RESPONSE_NEW_CONNECTION) != NULL)
	{
		ctx->events->cb_on_new_connection();
	}
	else if(ctx->events->cb_on_connection_secured&& 
			strstr(rn487x_get_response(), RN487X_RESPONSE_CONNECTION_SECURED) != NULL)
	{
		ctx->events->cb_on_connection_secured();
	}	
	else if(ctx->events->cb_on_disconnect &&
			strstr(rn487x_get_response(), RN487x_RESPONSE_DISCONNECT) != NULL)
	{
		ctx->events->cb_on_disconnect();
	}
	else if(ctx->events->cb_on_recieve_notification && 
				strstr(rn487x_get_response(), RN487x_RESPONSE_RECIEVE_NOTIFICATION) != NULL)
	{
		ctx->events->cb_on_recieve_notification();
	}
	else if(ctx->events->cb_on_recieve_write_request &&
		strstr(rn487x_get_response(), RN487x_RESPONSE_RECIEVE_WRITE_REQUEST) != NULL)
	{
		ctx->events->cb_on_recieve_write_request();
	}
	else if(ctx->events->cb_on_bond && 
		strstr(rn487x_get_response(), RN487x_RESPONSE_BONDED) != NULL)
	{
		ctx->events->cb_on_bond();
	}
	// for custom events
	if(ctx->events->cb_on_uart_response && rx_wptr > 0)
	{
		ctx->events->cb_on_uart_response();
	}


	rn487x_clear_rx_buff();
}

static void rn487x_main_loop(struct ble_server* ctx)
{
	// enter pressed
	if(usb_rx_wptr > 0 && rn487x_usb_rx_buff[usb_rx_wptr-1] == 13) 
	{
		rn487x_usb_rx_buff[usb_rx_wptr] = '\n';
		rn487x_usb_rx_buff[usb_rx_wptr+1] = '\0';

		// send cmd
		rn487x_send_ascii_command(rn487x_usb_rx_buff);

		// reset buffer
		memset(rn487x_usb_rx_buff, NULL, RN487X_USB_CDC_BUFF_SIZE);
		usb_rx_wptr = 0;
	}

	_delay_ms(300);
	//parse responses
	// on connection
	// on disconnect
	// on characteristic write
	//	

	printf("%s", rn487x_get_response());
	rn487x_parse_responses(ctx);
	//rn487x_clear_rx_buff();
}

ble_error_t rn487x_init(struct ble_server* ctx)
{

	#ifdef PRINT_DEBUG_MSG
	printf("\r\nInitializing rn487x\r\n");
	#endif

	rx487x_set_ISR_cb(rn487x_cb_isr, RX_CB);
	usb_cdc_set_ISR_cb(rn487x_usb_cdc_isr, RX_CB);

	ctx->sys->reboot(ctx);
	ctx->sys->factory_reset(ctx);

	rn487x_gap_init(ctx);
	rn487x_gatt_init(ctx);

	rn487x_clear_rx_buff();
	_delay_ms(100);
}

/* SYS OPS */

static ble_error_t rx487x_shutdown(struct ble_server* ctx) 
{
	RN487X_RST_set_level(false);
	
	return 1;
}

static ble_error_t rx487x_reboot(struct ble_server* ctx)
{
	rn487x_clear_rx_buff();
	RN487X_RST_set_level(false);
	_delay_ms(RN487X_RESET_DELAY);
	RN487X_RST_set_level(true);
	_delay_ms(RN487X_STARTUP_TIME);
	
	if(strstr(rn487x_rx_buff, "%REBOOT%"))
	{
		return 1;
	}
	else
	{
		//perror("Failed to reboot\r\n");
		return 0;
	}

}

static ble_error_t rx487x_factory_reset(struct ble_server* ctx)
{	
	rn487x_send_ascii_command("SF,2\r\n");
	return rn487x_get_err_from_response();

	if(strstr(rn487x_rx_buff, "Reboot"))
	{
		return 1;
	}
	else
	{
		//perror("Factory reset failed\r\n");
		return 0;
	}
}

static struct ble_sys_ops rn487x_sys_ops = {
	
	.shutdown = rx487x_shutdown,
	.reboot	= rx487x_reboot,
	.factory_reset = rx487x_factory_reset,
	
};

/* GATT OPS */

ble_error_t rn487x_read_value(struct gatt_characteristic* characteristic, uint8_t destination[])
{
	return rn487x_read_handle(characteristic->handle, characteristic->data_len, destination);
}

ble_error_t rn487x_write_value(struct gatt_characteristic* characteristic, const uint8_t payload[])
{
	return rn487x_write_handle(characteristic->handle, characteristic->data_len, payload);
}

static struct ble_gatt_ops rn487x_gatt_ops = {
	.read_value = rn487x_read_value,
	.write_value = rn487x_write_value,
};

/* GAP OPS */

ble_error_t rn487x_start_advertising(struct ble_server* ctx)
{
	rn487x_send_ascii_command("A\r\n");
}

ble_error_t rn487x_stop_advertising(struct ble_server* ctx)
{
	rn487x_send_ascii_command("Y\r\n");
}

ble_error_t rn487x_kill_connection(struct ble_server* ctx)
{
	rn487x_send_ascii_command("K,1\r\n");
}

ble_error_t rn487x_clear_bonding_info(struct ble_server* ctx)
{
	rn487x_send_ascii_command("U,Z\r\n");
}

static struct ble_gap_ops rn487x_gap_ops = {					
	.start_advertising = rn487x_start_advertising,
	.stop_advertising = rn487x_stop_advertising,
	.kill_connection = rn487x_kill_connection,
	.clear_bonding_info = rn487x_clear_bonding_info,
};

/* Helper GATT Functions */

ble_error_t rn487x_gatt_init(struct ble_server* ctx)
{
	// register services and characteristics
	struct gatt_service	*(*services)[]	= ctx->config->services;

	for(short i = 0; i < ctx->config->services_count; i++)
	{
		struct gatt_service* service = (*services)[i];
		
		rn487x_register_service(service);

		struct gatt_characteristic *(*characteristics)[] = service->characteristics;

		for(short j = 0; j < service->characteristics_count; j++)
		{
			struct gatt_characteristic* characteristic = (*characteristics)[j];

			if(rn487x_register_characteristic(characteristic))
			{
				uint8_t buff[50];
				uint8_t* res;

				// list all characteristics in the service
				sprintf(buff, "LS,%s\r\n", service->UUID);
				rn487x_send_ascii_command(buff);

				// find this characteristic from the LS
				// XXXX...X,0000,00
				res = strstr(rn487x_rx_buff, characteristic->UUID);
				res =  res +  strlen(characteristic->UUID) + 1;
				
				//uint8_t* endptr;
				characteristic->handle = strtol(res, NULL, 16);

				#ifdef PRINT_DEBUG_MSG
				printf("Registered characteristic %s, with handle %04X\r\n", characteristic->UUID, characteristic->handle);
				#endif
			}
			else
			{
				return BLE_FAIL;
			}
		}
	}

	ctx->sys->reboot(ctx);
	rn487x_send_ascii_command("LS\r\n");
	return BLE_NOERR;
}

ble_error_t rn487x_register_service(struct gatt_service* service)
{
	sprintf(rn487x_cmd_buff_a, "PS,%s\r\n", service->UUID);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
	return rn487x_get_err_from_response();
}

ble_error_t rn487x_register_characteristic(struct gatt_characteristic* characteristic)
{
	sprintf(rn487x_cmd_buff_a, "PC,%s,%02X,%02X\r\n", characteristic->UUID, characteristic->properties, characteristic->data_len);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
	return rn487x_get_err_from_response();
}

/* Helper GAP Functions */

ble_error_t rn487x_set_address(struct ble_server* ctx, const uint8_t payload[])
{
	char *ptr = &rn487x_cmd_buff_b[0];

	int i;

	for (i = 0; i < MAC_ADDRESS_BYTE_LEN; i++)
	{
		ptr += sprintf(ptr, "%02X", payload[i]);
	}

	sprintf(rn487x_cmd_buff_a, "&,%s\r\n", rn487x_cmd_buff_b);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
}

ble_error_t rn487x_set_device_name(struct ble_server* ctx, const uint8_t* name)
{
	sprintf(rn487x_cmd_buff_a, "S-,%s\r\n", name);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
}

ble_error_t rn487x_set_appearance(struct ble_server* ctx, const ble_gap_appearance_t appearance)
{
	sprintf(rn487x_cmd_buff_a, "SDA,%04X\r\n", appearance);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
}

ble_error_t rn487x_set_connection_params(struct ble_server* ctx,
											const uint16_t min_interval,
											const uint16_t max_interval,
											const uint16_t latency,
											const uint16_t timeout)
{
	// ST,<hex16>,<hex16>,<hex16>,<hex16>
	sprintf(rn487x_cmd_buff_a, "ST,%04X,%04X,%04X,%04X\r\n",
	min_interval, max_interval, latency, timeout);

	rn487x_send_ascii_command(rn487x_cmd_buff_a);

}

ble_error_t rn487x_set_security(struct ble_server* ctx,
										const ble_io_capabilities_t io_capabilities,
										const uint8_t* passkey)
{
	sprintf(rn487x_cmd_buff_a, "SA,%d\r\n", io_capabilities);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);

	sprintf(rn487x_cmd_buff_a, "SP,%s\r\n", passkey);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
}

ble_error_t rn487x_gap_init(struct ble_server* ctx)
{
	if(ctx->config->address != NULL)
		rn487x_set_address(ctx, ctx->config->address);

	if(ctx->config->device_name != NULL)
		rn487x_set_device_name(ctx, ctx->config->device_name);

	rn487x_set_security(ctx, ctx->config->io_capabilities, ctx->config->passkey);
	rn487x_set_appearance(ctx, ctx->config->advertisement_appearance);
	rn487x_set_connection_params(ctx, ctx->config->connection_min_interval, ctx->config->connection_max_interval, ctx->config->connection_latency, ctx->config->connection_timeout);
	
	ctx->sys->reboot(ctx);
}

/* Helper ASCII Functions */

ble_error_t rn487x_read_handle(uint8_t handle, uint8_t data_len, uint8_t destination[])
{
	sprintf(rn487x_cmd_buff_a, "SHR,%04X\r\n", handle);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
	
	if(rn487x_get_err_from_response())
	{
		strncpy(rn487x_cmd_buff_a, (rn487x_rx_buff + 5), (data_len * 2));
		uint8_t *pos = 	rn487x_cmd_buff_a;

		for (short i = 0; i < data_len; i++)
		{
			sscanf(pos, "%2hhX", &destination[i]);
			pos = pos + 2;
		}

	}
	else
	{
		return BLE_FAIL;
	}
}

ble_error_t rn487x_write_handle(uint8_t handle, uint8_t data_len, const uint8_t payload[])
{
	char *ptr = &rn487x_cmd_buff_b[0];

	int i;

	for (i = 0; i < data_len; i++)
	{
		ptr += sprintf(ptr, "%02X", payload[i]);
	}

	sprintf(rn487x_cmd_buff_a, "SHW,%04X,%s\r\n", handle, rn487x_cmd_buff_b);
	rn487x_send_ascii_command(rn487x_cmd_buff_a);
}


static void rn487x_clear_rx_buff()
{
	rx_wptr = 0;
	memset(rn487x_rx_buff, 0, RN487X_RX_BUFF_SIZE);
}

static ble_error_t rn487x_get_err_from_response()
{
	if(	strstr(rn487x_rx_buff, RN487X_RESPONSE_ERR) != NULL)
	return 0;
	else
	return 1;

}


static void rn487x_cb_isr()
{
	rn487x_rx_buff[rx_wptr] = rx487x_get_data();
	rx_wptr = (rx_wptr + 1) & RN487X_RX_BUFF_MASK;
}

void rn487x_send_ascii_command(const uint8_t* cmd)
{
	uint8_t id = 0;
	

	rn487x_clear_rx_buff();
	
	// enter cmd mode
	rx487x_write('$');
	rx487x_write('$');
	rx487x_write('$');

	_delay_ms(100);

	while(cmd[id] != NULL)
	{
		if(rx487x_is_tx_ready())
		{
			rx487x_write(cmd[id]);
			id++;
		}
	}

	_delay_ms(RN487X_DELAY_WAIT_FOR_RESPONSE);

	//exit cmd mode
	rx487x_write('-');
	rx487x_write('-');
	rx487x_write('-');
	rx487x_write('\r');
	rx487x_write('\n');

	_delay_ms(100);
	
	#ifdef PRINT_DEBUG_MSG
	printf("%s", cmd);
	printf("%s", rn487x_rx_buff);
	#endif

}

void rn487x_usb_cdc_isr()
{

	if(usb_rx_wptr < (RN487X_USB_CDC_BUFF_SIZE - 2))
	{
		rn487x_usb_rx_buff[usb_rx_wptr] = usb_cdc_get_data();
		printf("%c", rn487x_usb_rx_buff[usb_rx_wptr]);
		usb_rx_wptr = (usb_rx_wptr + 1);
	}
	else
	{
		usb_cdc_get_data();
	}


	
}

uint8_t* rn487x_get_response(void)
{
	return rn487x_rx_buff;
}