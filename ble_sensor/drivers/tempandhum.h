#ifndef TEMPANDHUM_H
#define TEMPANDUHM_H

#include <i2c_simple_master.h>

#define TEMPANDHUM_I2C_ADDR											0x5F
#define TEMPANDHUM_I2C_ADDR_WRITE									0xBE
#define TEMPANDHUM_I2C_ADDR_READ									0xBF

//register addresses
#define TEMPANDHUM_WHO_AM_I											0x0F

#define TEMPANDHUM_TEMP_OUT_L										0x2A
#define TEMPANDHUM_TEMP_OUT_H										0x2B



#define TEMPANDHUM_HUMIDITY_OUT_L 									0x28
#define TEMPANDHUM_HUMIDITY_OUT_H 									0x29

#define TEMPANDHUM_AV_CONF                                          0x10
#define TEMPANDHUM_CTRL_REG1                                        0x20
#define TEMPANDHUM_CTRL_REG2                                        0x21
#define TEMPANDHUM_CTRL_REG3                                        0x22

#define TEMPANDHUM_STATUS_REG                                       0x27 // bit0 - temp data available, bit1 - hum data available

//default values

#define TEMPANDHUM_AV_CONF_DEFAULT_VALUE							0x1B
#define TEMPANDHUM_CTRL_REG1_DEFAULT_VALUE                          0xE7 //01100111
#define TEMPANDHUM_CTRL_REG2_DEFAULT_VALUE                          0x00
#define TEMPANDHUM_CTRL_REG3_DEFAULT_VALUE                          0x00

#define TEMPANDHUM_REG_CALIB_H0_RH_X2								 0x30
#define TEMPANDHUM_REG_CALIB_H1_RH_X2 0x31

#define TEMPANDHUM_REG_CALIB_T1_T0_MSB								 0x35
#define TEMPANDHUM_REG_CALIB_H0_T0_OUT_L							 0x36
#define TEMPANDHUM_REG_CALIB_H0_T0_OUT_H							 0x37
#define TEMPANDHUM_REG_CALIB_H1_T0_OUT_L							 0x3A
#define TEMPANDHUM_REG_CALIB_H1_T0_OUT_H							 0x3B

#define TEMPANDHUM_REG_CALIB_T0_DEGC_X8								 0x32
#define TEMPANDHUM_REG_CALIB_T1_DEGC_X8								 0x33

#define TEMPANDHUM_REG_CALIB_T0_OUT_L								 0x3C
#define TEMPANDHUM_REG_CALIB_T0_OUT_H								 0X3D

#define TEMPANDHUM_REG_CALIB_T1_OUT_L								 0x3E
#define TEMPANDHUM_REG_CALIB_T1_OUT_H								 0x3F


void tempandhum_init(void);

void tempandhum_test(void);

float temphum_get_temp(void);
float temphum_get_humidity(void);


#endif