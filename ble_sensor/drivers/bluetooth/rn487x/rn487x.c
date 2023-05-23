#include <drivers/bluetooth/ble.h>
#include "rn487x.h"

#define PRINT_DEBUG_MSG


#define RN487X_RX_BUFF_SIZE  256

#define RN487X_RX_BUFF_MASK (RN487X_RX_BUFF_SIZE - 1)


#define RN487X_RESET_DELAY (10)
#define RN487X_STARTUP_TIME (300)
#define RN487X_DELAY_WAIT_FOR_RESPONSE (300)

#define RN487X_MAX_SUPPORTED_PRIVATE_SERVICES (4)
#define RN487X_MAX_SUPPORTED_CHARACTERISTICS_PER_SERVICE (8)

#define RN487X_TEMP_AND_HUM_SERVICE_UUID "2A981F4C744841F883E88BF97FE46381"
#define RN487X_TEMP_READ_CHARACTERISTIC_UUID "73657BD82D044C31A31E54DE1DAB66FF"
#define RN487X_HUM_READ_CHARACTERISTIC_UUID "D0A512D60D8145C2BEDD621EF1CBBEFB"

#define RN487X_RESPONSE_ERR "Err"

static volatile uint8_t rn487x_rx_buff[RN487X_RX_BUFF_SIZE];
static volatile size_t rx_wptr = 0;



static struct ble_sys_ops rn487x_sys_ops;
static struct ble_gatt_ops rn487x_gatt_ops;
static struct ble_gap_ops rn487x_gap_ops;



static void rn487x_clear_rx_buff(void);
static void rn487x_init(struct ble_server*);
static void rn487x_probe(void);
static void rn487x_cb_isr(void);

static ble_error_t rn487x_get_err_from_response();


static struct gatt_service *rn487x_services[] = {&temp_and_hum_service};

static struct gatt_characteristic *temp_and_hum_characteristics[] = 
	{&temp_read_characteristic, &humidity_read_characteristic};


struct gatt_characteristic temp_read_characteristic = {
	.UUID = RN487X_TEMP_READ_CHARACTERISTIC_UUID,
	.properties = BLE_PROP_FLAG_READ,
	.data_len = 1,
};

struct gatt_characteristic humidity_read_characteristic = {
	.UUID = RN487X_HUM_READ_CHARACTERISTIC_UUID,
	.properties = BLE_PROP_FLAG_READ,
	.data_len = 1,	
};

struct gatt_service temp_and_hum_service = {
	.UUID = "2A981F4C744841F883E88BF97FE46381",
	.characteristics = &temp_and_hum_characteristics,
	.characteristics_count = 2,
};

struct ble_server rn487x = {
	.device_name = "rn4870",
	.enable_bonding = false,
	.io_capabilities = IO_CAPS_KEYBOARD_DISPLAY,
	.passkey = "123456",
	.advertisement_appearance = BLE_APPEARANCE_UNKNOWN,
	.advertisment_type = CONNECTABLE_UNDIRECTED,
	.advertisement_interval = 0x0020,
	.advertisement_timeout = 0x0003,
	.services_count = 1,
	.services = &rn487x_services,
	.sys = &rn487x_sys_ops,
	.gatt = &rn487x_gatt_ops,
	.gap = &rn487x_gap_ops,
	
	.init = rn487x_init,
	//.probe = rn487x_probe,
	
};

static ble_error_t rx487x_shutdown(struct ble_server* ctx) 
{
	RN487X_RST_set_level(false);
	
	return BLE_NOERR;
}

static ble_error_t rx487x_reboot(struct ble_server* ctx)
{
	rn487x_clear_rx_buff();
	RN487X_RST_set_level(false);
	_delay_ms(RN487X_RESET_DELAY);
	RN487X_RST_set_level(true);
	_delay_ms(RN487X_STARTUP_TIME);
	
	return rn487x_get_err_from_response();
}

static ble_error_t rx487x_factory_reset(struct ble_server* ctx)
{	
	rn487x_send_ascii_command("SF,2\r\n");
	return rn487x_get_err_from_response();
}

static struct ble_sys_ops rn487x_sys_ops = {
	
	.shutdown = rx487x_shutdown,
	.reboot	= rx487x_reboot,
	.factory_reset = rx487x_factory_reset,
	
};

static ble_error_t rn487x_register_service(struct gatt_service* service)
{
	uint8_t buff[50];
	sprintf(buff, "PS,%s\r\n", service->UUID);
	rn487x_send_ascii_command(buff);
	return rn487x_get_err_from_response();
}

static ble_error_t rn487x_register_characteristic(struct gatt_characteristic* characteristic)
{
	uint8_t buff[50];
	sprintf(buff, "PC,%s,%02X,%02X\r\n", characteristic->UUID, characteristic->properties, characteristic->data_len);
	rn487x_send_ascii_command(buff);
	return rn487x_get_err_from_response();
}

static ble_error_t rn487x_read_value(struct gatt_characteristic* characteristic)
{
	uint8_t data[(characteristic->data_len * 2 ) + 1];
	sprintf(data, "SHR,%04X\r\n", characteristic->handle);
	rn487x_send_ascii_command(data);
	
	if(rn487x_get_err_from_response())
	{
		strncpy(characteristic->data, (rn487x_rx_buff + 5), (characteristic->data_len * 2));
		characteristic->data[characteristic->data_len * 2] = '\0';
	}
	else
	{
		return BLE_FAIL;
	}


}

static ble_error_t rn487x_write_value(struct gatt_characteristic* characteristic, const uint8_t payload[])
{

	uint8_t hexcode[(characteristic->data_len * 2 ) + 1];
	uint8_t cmd[(characteristic->data_len * 2 ) + 10];

	char *ptr = &hexcode[0];

	int i;

	for (i = 0; i < characteristic->data_len; i++) {
		ptr += sprintf(ptr, "%02X", payload[i]);
	}

	sprintf(cmd, "SHW,%04X,%s\r\n", characteristic->handle, hexcode);
	rn487x_send_ascii_command(cmd);
}

static ble_error_t rn487x_gatt_init(struct ble_server* ctx)
{
	// register services and characteristics
	struct gatt_service	*(*services)[]	= ctx->services;

	for(short i = 0; i < ctx->services_count; i++)
	{
		struct gatt_service* service = (*services)[i];
	
		ctx->gatt->register_service(service);

		struct gatt_characteristic *(*characteristics)[] = service->characteristics;

		for(short j = 0; j < service->characteristics_count; j++)
		{
			struct gatt_characteristic* characteristic = (*characteristics)[j];

			if(ctx->gatt->register_characteristic(characteristic))
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

				//allocate data
				characteristic->data = (uint8_t*)malloc((characteristic->data_len * 2 + 1 ) * sizeof(uint8_t));

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

static struct ble_gatt_ops rn487x_gatt_ops = {
	.register_service = rn487x_register_service,
	.register_characteristic = rn487x_register_characteristic,
	.read_value = rn487x_read_value,
	.write_value = rn487x_write_value,
	.init = rn487x_gatt_init,
};


static struct ble_gap_ops rn487x_gap_ops = {

};

static void rn487x_init(struct ble_server* ctx)
{

#ifdef PRINT_DEBUG_MSG
	printf("\r\nInitializing rn487x\r\n");
#endif

	rx487x_set_ISR_cb(rn487x_cb_isr, RX_CB);

	ctx->sys->reboot(ctx);
	ctx->sys->factory_reset(ctx);

	//init gap services

	// init gatt services 
	ctx->gatt->init(ctx);


}

static void rn487x_clear_rx_buff()
{
	rx_wptr = 0;
	memset(rn487x_rx_buff, 0, RN487X_RX_BUFF_SIZE);
}

static ble_error_t rn487x_get_err_from_response()
{
	if(	strstr(rn487x_rx_buff, RN487X_RESPONSE_ERR) != NULL)
	return BLE_FAIL;
	else
	return BLE_NOERR;

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