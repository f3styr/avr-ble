#include <atmel_start.h>
#include <util/delay.h>
#include <atmel_start_pins.h>
#include <atomic.h>
#include <drivers/mcp9844.h>
#include <drivers/bma253.h>
#include <drivers/bluetooth/ble.h>
#include <drivers/tempandhum.h>
#include <drivers/bluetooth/rn487x/rn487x.h>

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
	ENABLE_INTERRUPTS();
	
	
	atmel_start_init();


	temp_read_characteristic.data_len = 10;
	rn487x.init(&rn487x);
	volatile uint8_t data[] = {0x23, 0x33, 0x44, 0x55, 0xAA, 0xFF, 0xDD, 0xAA, 0x33, 0xAA };	
	rn487x.gatt->write_value(&temp_read_characteristic, data);
	rn487x.gatt->write_value(&temp_read_characteristic, data);
	rn487x.gatt->read_value(&temp_read_characteristic, data);
	

	while(1) {
		rn487x.main_loop(&rn487x);
		//printf(rn487x_get_response());
		//rn487x_send_ascii_command("GK\r\n");
		
	}
}
