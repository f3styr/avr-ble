#include "tempandhum.h"
#include <util/delay.h>
#include <port.h>


i2c_error_t err;

int16_t H0_RH_X2, H1_RH_X2, T0_DEGC_X8, T1_DEGC_X8, T1_T0_MSB, H0_T0, H1_T0, T0_OUT, T1_OUT;


void tempandhum_init(void)
{

	_delay_ms(1000);		

	err = i2c_write1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_AV_CONF, TEMPANDHUM_AV_CONF_DEFAULT_VALUE);
	err = i2c_write1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_CTRL_REG1,TEMPANDHUM_CTRL_REG1_DEFAULT_VALUE);	
	err = i2c_write1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_CTRL_REG2, TEMPANDHUM_CTRL_REG2_DEFAULT_VALUE);	
	err = i2c_write1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_CTRL_REG3, TEMPANDHUM_CTRL_REG3_DEFAULT_VALUE);

	calibrate();
}

void calibrate()
{
	    int16_t data = 0;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_H0_RH_X2);
	    H0_RH_X2 = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_H1_RH_X2);
	    H1_RH_X2 = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T0_DEGC_X8);
	    T0_DEGC_X8 = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T1_T0_MSB);
	    T0_DEGC_X8 |= (data & 0x03) << 8;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T1_DEGC_X8);
	    T1_DEGC_X8 = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T1_T0_MSB);
	    T1_DEGC_X8 |= (data & 0x0C) << 6;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_H0_T0_OUT_L);
	    H0_T0 = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_H0_T0_OUT_H);
	    H0_T0 |= data << 8;

	    if (H0_T0 > 32768) {
		    H0_T0 -= 65536;
	    }

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_H1_T0_OUT_L);
	    H1_T0 = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_H1_T0_OUT_H);
	    H1_T0 |= data << 8;

	    if (H1_T0 > 32768) {
		    H1_T0 -= 65536;
	    }

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T0_OUT_L);
	    T0_OUT = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T0_OUT_H);
	    T0_OUT |= data << 8;

	    if (T0_OUT > 32768) {
		    T0_OUT -= 65536;
	    }

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T1_OUT_L);
	    T1_OUT = data;

	    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_REG_CALIB_T1_OUT_H);
	    T1_OUT |= data << 8;

	    if (T1_OUT > 32768) {
		    T1_OUT -= 65536;
	    }
}

float temphum_get_humidity(void)
{
    int32_t data = 0;
    int32_t humidity = 0;

    data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_STATUS_REG);


    if (!(data & 0x02)) 
	{
	    //printf("sensor not ready\r\n");
		return 0;
    }


	data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_HUMIDITY_OUT_L);
	humidity = data;
	
	data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_HUMIDITY_OUT_H);
	humidity |= data << 8;
			
    if (humidity > 32768) {
	    humidity -= 65536;
    }

    float result = H0_RH_X2 / 2.0 + (humidity - H0_T0) * (H1_RH_X2 - H0_RH_X2) / 2.0 / (H1_T0 - H0_T0);
	
	return result;
}

float temphum_get_temp(void)
{

	int32_t data = 0;
	int32_t temperature = 0;
	
	data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_STATUS_REG);
	
	if(!(data & 0x01))
	{
		//printf("sensor not ready\r\n");
		return 0; //
	}
	else
	{
		data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_TEMP_OUT_L);
		temperature = data;
		
		data = i2c_read1ByteRegister(TEMPANDHUM_I2C_ADDR, TEMPANDHUM_TEMP_OUT_H);
		temperature |= data << 8;
	}
		
	if (temperature > 32768) 
	{
		temperature -= 65536;
	}

	float result = T0_DEGC_X8 / 8.0 + (temperature - T0_OUT) * (T1_DEGC_X8 - T0_DEGC_X8) / 8.0 / (T1_OUT - T0_OUT);
	
	return result;

	
}
