/**
 * \file
 *
 * \brief USART basic driver.
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

#ifndef USART_BASIC_H_INCLUDED
#define USART_BASIC_H_INCLUDED

#include <atmel_start.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Normal Mode, Baud register value */
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(3333333 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

/* rx487x Ringbuffer */

#define rx487x_RX_BUFFER_SIZE 256
#define rx487x_TX_BUFFER_SIZE 256
#define rx487x_RX_BUFFER_MASK (rx487x_RX_BUFFER_SIZE - 1)
#define rx487x_TX_BUFFER_MASK (rx487x_TX_BUFFER_SIZE - 1)

typedef enum { RX_CB = 1, UDRE_CB } usart_cb_type_t;
typedef void (*usart_cb_t)(void);

int8_t rx487x_init();

void rx487x_enable();

void rx487x_enable_rx();

void rx487x_enable_tx();

void rx487x_disable();

uint8_t rx487x_get_data();

bool rx487x_is_tx_ready();

bool rx487x_is_rx_ready();

bool rx487x_is_tx_busy();

uint8_t rx487x_read(void);

void rx487x_write(const uint8_t data);

void rx487x_set_ISR_cb(usart_cb_t cb, usart_cb_type_t type);

/* Normal Mode, Baud register value */
#define USART2_BAUD_RATE(BAUD_RATE) ((float)(3333333 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

/* usb_cdc Ringbuffer */

#define usb_cdc_RX_BUFFER_SIZE 256
#define usb_cdc_TX_BUFFER_SIZE 256
#define usb_cdc_RX_BUFFER_MASK (usb_cdc_RX_BUFFER_SIZE - 1)
#define usb_cdc_TX_BUFFER_MASK (usb_cdc_TX_BUFFER_SIZE - 1)

int8_t usb_cdc_init();

void usb_cdc_enable();

void usb_cdc_enable_rx();

void usb_cdc_enable_tx();

void usb_cdc_disable();

uint8_t usb_cdc_get_data();

bool usb_cdc_is_tx_ready();

bool usb_cdc_is_rx_ready();

bool usb_cdc_is_tx_busy();

uint8_t usb_cdc_read(void);

void usb_cdc_write(const uint8_t data);

void usb_cdc_set_ISR_cb(usart_cb_t cb, usart_cb_type_t type);

#ifdef __cplusplus
}
#endif

#endif /* USART_BASIC_H_INCLUDED */
