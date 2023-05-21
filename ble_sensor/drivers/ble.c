#include "ble.h"


static void rn4870_init(void);
static void rn4870_isr(void);
static bool rn4870_send_command(const uint8_t*);
static void rn4870_characteristic_send_data(const uint8_t*, const int16_t);
static int16_t rn4870_characteristic_get_data(const uint8_t*);
static uint8_t* rn4870_get_response(void); 
static void rn4870_reboot(void);

volatile uint8_t ble_cmd_buff[BLE_CMD_BUFF_SIZE];
volatile uint8_t ble_rx_buff[BLE_RX_BUFF_SIZE];
volatile size_t ble_wptr = 0;


const ble_ascii_interface rn4870 = 
{
	.init = rn4870_init,
	.usart_interrupt_routine = rn4870_isr,
	.send_command = rn4870_send_command,
	.get_response = rn4870_get_response,
	.characteristic_send_data = rn4870_characteristic_send_data,
	.characteristic_get_data = rn4870_characteristic_get_data,
	.reboot = rn4870_reboot,
};

static void rn4870_init(void)
{
	//printf("\e[1;1H\e[2J"); // clear console
	
	// set interrupt callback
	rx487x_set_ISR_cb(rn4870.usart_interrupt_routine, RX_CB);
	
	rn4870.reboot(); // starts ble
	
	rn4870.send_command(BLE_CMD_ENTER_CMD_MODE);
	rn4870.send_command(BLE_CMD_FACTORY_RESET); 
	
	// factory reset reboots ble
	rn4870.send_command(BLE_CMD_ENTER_CMD_MODE);
	
	// set device name
	rn4870.send_command(BLE_CMD_FN_SET_BT_NAME);
	rn4870.send_command(BLE_CMD_FN_SET_DEV_NAME);
	
	// register characteristics
	rn4870.send_command(BLE_CMD_FN_REGISTER_SERVICE_TEMP);
	rn4870.send_command(BLE_CMD_FN_REGISTER_CHARACTERISTIC_TEMP_READ);	
	rn4870.send_command(BLE_CMD_FN_REGISTER_CHARACTERISTIC_HUMIDITY_READ);	
	
	//rn4870.send_command(BLE_CMD_FN_REGISTER_SERVICE_HUM);
	
	
	// reboot to update the characteristics
	rn4870.reboot();
	
	rn4870.send_command(BLE_CMD_ENTER_CMD_MODE);
	rn4870.send_command(BLE_CMD_LIST_ACTIVE_SERVICES);
	
	

	printf("RN4870 Initialized in CMD mode\n\r");
	printf("\n\rActive services:\r\n%s", rn4870.get_response());

}

static void rn4870_characteristic_send_data(const uint8_t* characteristic_handle, const int16_t value) 
{
	sprintf(ble_cmd_buff, "SHW,%s,%X\r\n", characteristic_handle, value);
	printf("%s\r\n", ble_cmd_buff);
	rn4870.send_command(ble_cmd_buff);
}

static int16_t rn4870_characteristic_get_data(const uint8_t* characteristic_handle) 
{
	sprintf(ble_cmd_buff, "SHR,%s\r\n", characteristic_handle);
	rn4870.send_command(ble_cmd_buff);
	
	return strtol(ble_rx_buff, NULL, 16);

}

static void rn4870_isr(void) 
{
	ble_rx_buff[ble_wptr] = rx487x_get_data();
	ble_wptr = (ble_wptr + 1) & BLE_RX_BUFF_MASK;	
}

static uint8_t* rn4870_get_response(void) 
{
	return ble_rx_buff;
}



static void rn4870_reboot(void)
{
	ble_wptr = 0;
		
	RN487X_RST_set_level(false);
	_delay_ms(BLE_RESET_DELAY);
	RN487X_RST_set_level(true);
	_delay_ms(BLE_STARTUP_TIME);
}


static bool rn4870_send_command(const uint8_t* cmd)
{
	uint8_t id = 0;
	
	ble_wptr = 0;
	memset(ble_rx_buff, 0, BLE_RX_BUFF_SIZE);
	
	while(cmd[id] != NULL)
	{
		if(rx487x_is_tx_ready())
		{
			rx487x_write(cmd[id]);
			id++;
		}
	}

	_delay_ms(BLE_DELAY_BETWEEN_COMMANDS);
		
	if(strstr(rn4870_get_response(), BLE_RESPONSE_ERR) != NULL)
	{
		printf("\n\r%s : %s\r\n", cmd, rn4870_get_response());
	}

}

