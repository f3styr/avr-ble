#include <atmel_start.h>
#include <atomic.h>
#include <interrupt_avr8.h>
#include <usart_basic.h>
#include <util/delay.h>



#define CONFIG_USB_RX_BUFF_SIZE			256
#define CONFIG_USB_RX_BUFF_MASK			CONFIG_USB_RX_BUFF_SIZE - 1

static void usb_rx_data_cb(void);
//static void RN487X_SendCmd(const uint8_t *cmd, uint8_t cmdLen);

static volatile uint8_t usb_rx_buff[CONFIG_USB_RX_BUFF_SIZE];
static volatile size_t w_ptr;
static volatile bool rx_data_rdy;


int main(void)
{

	atmel_start_init();
	
	// If USART Basic driver is in IRQ-mode, enable global interrupts.
	ENABLE_INTERRUPTS();
	


	usb_cdc_set_ISR_cb(usb_rx_data_cb, RX_CB);

	//DATA_LED_SetHigh();

	PORTF_DIR


	while (1) {
			
		
		_delay_ms(500);
					
		//DATA_LED_SetHigh();		
		if(rx_data_rdy)
		{
			rx_data_rdy = false;
			printf("Received %s\r\n", usb_rx_buff);
		}
		
		
	}
}



static void usb_rx_data_cb(void)
{
	/* Get data */
	usb_rx_buff[w_ptr] = usb_cdc_get_data();
	/* Calculate next buffer index */
	w_ptr = (w_ptr + 1) & CONFIG_USB_RX_BUFF_MASK;
	/* Reset rx data rdy timer */
	rx_data_rdy = true;
}



