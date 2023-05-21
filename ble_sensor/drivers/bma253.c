#include "bma253.h"
#include <util/delay.h>
#include <i2c_simple_master.h>

#define DATA_READY_BITMASK  (0x01)

static volatile int bma253_x_accel;
static volatile int bma253_y_accel;
static volatile int bma253_z_accel;

static bool bma253_x_accel_data_ready(void) ;
static bool bma253_y_accel_data_ready(void) ;
static bool bma253_z_accel_data_ready(void) ;

i2c_error_t error;

void bma253_initialize(void)
{ 
	_delay_ms(1000);	
	
	//error = i2c_write1ByteRegister(BMA253_I2C_ADDR, 0x21, 0);
	error = i2c_write1ByteRegister(BMA253_I2C_ADDR, BMA253_PWR_MODE_ADDR, BMA253_NORMAL_MODE);
	
	error = i2c_write1ByteRegister(BMA253_I2C_ADDR, BMA253_BW_SELECT_ADDR, BMA253_BW_7_81HZ);

	error = i2c_write1ByteRegister(BMA253_I2C_ADDR, BMA253_RANGE_ADDR, BMA253_2G_RANGE);
	

}

void bma253_print_accel(void)
{	
	uint16_t x_accel, y_accel, z_accel;
	
    uint8_t lsb_data;
    uint8_t msb_data;
	
	while(!bma253_x_accel_data_ready()) {};
	
	lsb_data = i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_X_LSB);
	msb_data = i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_X_MSB);
	
	x_accel = ( (((int16_t)msb_data) << 8) | (lsb_data) ) >> 4;
	
	
	while(!bma253_y_accel_data_ready()) {};
		
	lsb_data = i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_Y_LSB);
	msb_data = i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_Y_MSB);	
	
	y_accel = ( (((int16_t)msb_data) << 8) | (lsb_data) ) >> 4;
	
	
	while(!bma253_z_accel_data_ready()) {};
		
	lsb_data = i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_Z_LSB);
	msb_data = i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_Z_MSB);	
	
	z_accel = ( (((int16_t)msb_data) << 8) | (lsb_data) ) >> 4;	
	

	printf("Accel : (%d, %d, %d)\r", x_accel, y_accel, z_accel);

}


static bool bma253_x_accel_data_ready(void) 
{ 
	bool new_data;
	
	return (i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_X_LSB) & DATA_READY_BITMASK); 
	
	return new_data;
}
static  bool bma253_y_accel_data_ready(void)
{
	bool new_data;
	
	new_data = (i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_Y_LSB) & DATA_READY_BITMASK);
	
	return new_data;
}
static  bool bma253_z_accel_data_ready(void)
{
	bool new_data;
	
	new_data = (i2c_read1ByteRegister(BMA253_I2C_ADDR, BMA253_ACCD_Z_LSB) & DATA_READY_BITMASK);
	
	return new_data;
}