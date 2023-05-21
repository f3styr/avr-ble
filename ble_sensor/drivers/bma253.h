#ifndef bma253_H
#define	bma253_H

//https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bma253-ds000.pdf

#define BMA253_I2C_ADDR  0x19

#define BMA253_ACCD_X_LSB 0x02
#define BMA253_ACCD_X_MSB 0x03

#define BMA253_ACCD_Y_LSB 0x04
#define BMA253_ACCD_Y_MSB 0x05

#define BMA253_ACCD_Z_LSB 0x06
#define BMA253_ACCD_Z_MSB 0x07


#define BMA253_PWR_MODE_ADDR                0x11
#define BMA253_RANGE_ADDR                   0x0F
#define BMA253_BW_SELECT_ADDR               0x10


#define BMA253_2G_RANGE                     0x03
#define BMA253_BW_7_81HZ                    0x08
#define BMA253_NORMAL_MODE                  0x00



void bma253_initialize(void);
void bma253_print_accel(void);


#endif