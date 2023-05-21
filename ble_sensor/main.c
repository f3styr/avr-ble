#include <atmel_start.h>
#include <util/delay.h>
#include <atmel_start_pins.h>
#include <atomic.h>
#include <drivers/mcp9844.h>
#include <drivers/bma253.h>
#include <drivers/ble.h>
#include <drivers/tempandhum.h>

#define TICK_RATE (1000 / 10.0)
#define BLE_BUFF_SIZE (256)
#define BLE_BUFF_MASK (BLE_BUFF_SIZE - 1)

static void ble_isr(void);
static void interrupt_routine(void);
static bool is_button_pressed(void);
static void ble_reboot(void);
static void ble_send_command(const uint8_t*);
static bool usart_recieve_complete();


static volatile long current_tick = 0;
static volatile long data_led_off_tick = 0;
static volatile bool err_led_on = false;
static volatile bool print_accel = false;

volatile uint8_t ble_rx_buff[BLE_BUFF_SIZE];
volatile size_t ble_wptr;
volatile size_t ble_rptr;


int main(void)
{

	
	atmel_start_init();
	_delay_ms(100);


	ENABLE_INTERRUPTS();

	
	tempandhum_init();
	//bma253_initialize();
	
	_delay_ms(100);
	// register callbacks
	usb_cdc_set_ISR_cb(interrupt_routine, RX_CB);

	rn4870.init();
	
		
	while (1) {
				

		_delay_ms(3000);
		current_tick++;

		
		rn4870.characteristic_send_data(BLE_HANDLE_TEMP_READ_CHARACTERISTIC, temphum_get_temp());	
		rn4870.characteristic_send_data(BLE_HANDLE_HUMIDITY_READ_CHARACTERISTIC, temphum_get_humidity());

							
		// disable led 1 second after the last console input
		if(current_tick > data_led_off_tick)
			PF4_set_level(true);
		
		bool buttonPressed = is_button_pressed();
		
		// enable led only if the button is pressed
		if(buttonPressed && !err_led_on)
		{
			

			PORTF_set_pin_level(5, false);
			err_led_on = true;
			//print_accel = !print_accel;
			
			rn4870.characteristic_send_data(BLE_HANDLE_TEMP_READ_CHARACTERISTIC, mcp9844_get_temperature());
			rn4870.characteristic_send_data(BLE_HANDLE_HUMIDITY_READ_CHARACTERISTIC, mcp9844_get_temperature());
					
		}
		else if(!buttonPressed && err_led_on)
		{
			//on release button

			PORTF_set_pin_level(5, true);
			err_led_on = false;
			
			
			int16_t temp = rn4870.characteristic_get_data(BLE_HANDLE_TEMP_READ_CHARACTERISTIC);
			printf("%x\r\n", temp);
		}
		
		if(print_accel)
			bma253_print_accel();
			

	}
}


static bool is_button_pressed(void)
{
	return PORTF_get_pin_level(3) == 0;
}

static void interrupt_routine(void)
{
	// 
	int8_t key = usb_cdc_get_data();
	

	PF4_set_level(false);
	data_led_off_tick = current_tick + TICK_RATE;
}




static bool usart_recieve_complete()
{
	return (USART0.STATUS & 0x80) == 0;
}

/*

		RN487x_send_with_feedback("SF,2\r\n", "Reboot", 40);
		RN487x_send_with_feedback("$$$", "CMD> ", 40);

sound(2);
 Reset end 
Set services and characteristics 
RN487x_send_with_feedback("PS,2A981F4C744841F883E88BF97FE46381\r\n", "AOK\r\n", 40);
RN487x_send_with_feedback("PC,73657BD82D044C31A31E54DE1DAB66FF,10,10\r\n", "AOK\r\n", 40);
RN487x_send_with_feedback("PC,D0A512D60D8145C2BEDD621EF1CBBEFB,08,10\r\n", "AOK\r\n", 40);
RN487x_send_with_feedback("PC,20EE0C35916D4B85AD7EA9B6F3BDBA7C,02,10\r\n", "AOK\r\n", 40);
RN487x_send_with_feedback("PC,5E40171DDA084AFC8B8D528F394D0FDF,10,10\r\n", "AOK\r\n", 40);
RN487x_send_with_feedback("SA,4\r\n", "AOK\r\n", 40);											// Set pairing mode
RN487x_send_with_feedback("SP,123456\r\n", "AOK\r\n", 40);										// Set pin code
RN487x_send_with_feedback("SGA,0\r\n", "AOK\r\n", 40);											// Set advertisement RF output power to lowest
RN487x_send_with_feedback("SGC,0\r\n", "AOK\r\n", 40);											// Set connected RF output power to highest
sound(2);


void kill_connection()
{
	RN487x_send_with_feedback("K,1", "AOK\r\n", 40);
}

RN487x_send_with_feedback("Y\r\n", "AOK\r\n", 40);		// Stop advertisement
RN487x_send_with_feedback("A\r\n", "AOK\r\n", 40);		// Start advertisement

uint8_t RN487x_send_with_feedback(const char *sendString, const char *response, uint16_t delay)
{
	uint8_t err = 0;
	uint8_t res;
	do {
		RN487x_flush_async_buffer();
		RN4870_SendString(sendString);
		RN4870_blockingWait(delay);
		res = RN487x_get_feedback(response);
	} while ((res == NO_RESPONSE) & (err++ != 2));
	
	return res;
}

void RN4870_SendBuffer(const char *buffer, uint8_t length)
{
	while (length--)
	RN4870_SendByte(*buffer++);
}


void RN4870_SendByte(uint8_t data)
{
	USART_ASYNC_write(data);
}




*/