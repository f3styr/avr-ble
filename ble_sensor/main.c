#include <atmel_start.h>
#include <util/delay.h>
#include <atmel_start_pins.h>
#include <atomic.h>
#include <drivers/mcp9844.h>
#include <drivers/bma253.h>
#include <drivers/bluetooth/ble.h>
#include <drivers/tempandhum.h>
#include <drivers/bluetooth/rn487x/rn487x.h>


#define WRITE_BUFF_LEN 50

void on_connect(void);
void on_disconnect(void);
void on_connection_secured(void);
void on_recieve_notification(void);
void on_uart_response(void);



uint8_t write_buff[WRITE_BUFF_LEN];
uint8_t tick_counter = 0;

int main(void)
{
	ENABLE_INTERRUPTS();
	
	
	atmel_start_init();

	tempandhum_init();	

	rn487x.events->cb_on_new_connection = on_connect;
	rn487x.events->cb_on_connection_secured = on_connection_secured;
	rn487x.events->cb_on_disconnect = on_disconnect;
	rn487x.events->cb_on_uart_response = on_uart_response;
	rn487x.events->cb_on_recieve_notification = on_recieve_notification;

	rn487x.init(&rn487x);


	while(1) {
		
		rn487x.main_loop(&rn487x);
		
		if(tick_counter > 10)
		{
			float value = temphum_get_temp();
			memset(write_buff, NULL, WRITE_BUFF_LEN);
			sprintf(write_buff, "%.2f C", value);
			rn487x.gatt->write_value(&temp_read_characteristic, write_buff);

			value = temphum_get_humidity();
			memset(write_buff, NULL, WRITE_BUFF_LEN);
			sprintf(write_buff, "%.2f rH", value);
			rn487x.gatt->write_value(&humidity_read_characteristic, write_buff);
			tick_counter = 0;
		}
		
		tick_counter++;
	}
}

void on_connect(void)
{

}

void on_disconnect()
{

}

void on_connection_secured(void)
{

}

void on_recieve_notification(void)
{

}

void on_uart_response(void)
{

}