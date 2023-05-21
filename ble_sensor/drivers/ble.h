#ifndef ble_H
#define	ble_H

#include <usart_basic.h>
#include <util/delay.h>

/*

Indicate				0b00100000 Indicate value of characteristic with acknowledgment from server to client
Notify					0b00010000 Notify value of characteristic without acknowledgment from server to client
Write					0b00001000 Write value of characteristic with acknowledgment from client to server
Write without response	0b00000100 Write value of characteristic without acknowledgment from client to server	
Read					0b00000010 Read value of characteristic. Value is sent from server to client
				//		0b00011010 = 10
*/

// constants
#define BLE_RX_BUFF_SIZE (256)
#define BLE_RX_BUFF_MASK (BLE_RX_BUFF_SIZE - 1)

#define BLE_CMD_BUFF_SIZE (128)

#define BLE_RESET_DELAY (10)
#define BLE_STARTUP_TIME (300)
#define BLE_DELAY_BETWEEN_COMMANDS (300)

#define BLE_RESPONSE_ERR "Err"

// commands
#define BLE_CMD_LIST_ACTIVE_SERVICES "LS\r\n"
#define BLE_CMD_ENTER_CMD_MODE "$$$"
#define BLE_CMD_FACTORY_RESET "SF,2\r\n"

// functions
#define BLE_CMD_FN_SET_BT_NAME "S-,AVRBLE\r\n"
#define BLE_CMD_FN_SET_DEV_NAME "SN,AVRBLE\r\n"


// services
#define BLE_CMD_FN_REGISTER_SERVICE_TEMP			     "PS,2A981F4C744841F883E88BF97FE46381\r\n"
#define BLE_CMD_FN_REGISTER_CHARACTERISTIC_TEMP_READ     "PC,73657BD82D044C31A31E54DE1DAB66FF,02,10\r\n"

#define BLE_CMD_FN_REGISTER_CHARACTERISTIC_HUMIDITY_READ "PC,D0A512D60D8145C2BEDD621EF1CBBEFB,02,10\r\n"

// handles
#define BLE_HANDLE_TEMP_READ_CHARACTERISTIC "0072"
#define BLE_HANDLE_HUMIDITY_READ_CHARACTERISTIC "0074"

typedef struct
{
	void (*init)(void);
	void (*usart_interrupt_routine)(void);
	bool (*send_command)(const uint8_t*);
	void (*characteristic_send_data)(const uint8_t*, const int16_t);
	int16_t (*characteristic_get_data)(const uint8_t*);
	uint8_t* (*get_response)(void);
	void (*reboot)(void);
	
}ble_ascii_interface;

extern const ble_ascii_interface rn4870;

#endif