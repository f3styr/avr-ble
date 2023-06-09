/**
 * \file
 *
 * \brief I2C master driver.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <i2c_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TWI0_BAUD(F_SCL, T_RISE) ((((((float)3333333 / (float)F_SCL)) - 10 - ((float)3333333 * T_RISE / 1000000))) / 2)

void i2c_init(void);

i2c_error_t i2c_open(i2c_address_t address);

i2c_error_t i2c_close(void);

i2c_error_t i2c_master_operation(bool read);

i2c_error_t i2c_master_write(void); // to be depreciated

i2c_error_t i2c_master_read(void); // to be depreciated

void i2c_set_timeout(uint8_t to);

void i2c_set_baud_rate(uint32_t baud);

void i2c_set_buffer(void *buffer, size_t bufferSize);

// Event Callback functions.

void i2c_set_data_complete_callback(i2c_callback cb, void *p);

void i2c_set_write_collision_callback(i2c_callback cb, void *p);

void i2c_set_address_nack_callback(i2c_callback cb, void *p);

void i2c_set_data_nack_callback(i2c_callback cb, void *p);

void i2c_set_timeout_callback(i2c_callback cb, void *p);

#ifdef __cplusplus
}
#endif

#endif /* I2C_MASTER_H_INCLUDED */
