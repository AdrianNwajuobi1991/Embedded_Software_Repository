/*
 * USART_Driver.h
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */

#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include "DMA_Driver.h"


typedef struct USART_TypeDef_t * usart_device;

enum {
	OVERSAMPLE_16X, OVERSAMPLE_8X
};

enum {
	RX_INTERRUPT_ENABLE, TX_INTERRUPT_ENABLE, RX_INTERRUPT_DISABLE, TX_INTERRUPT_DISABLE
};

typedef struct USART_Config {
	bool use_tx_interrupt;
	bool use_rx_interrupt;
	bool use_error_interrupts;
	int8_t oversampling_mode;
	uint32_t baud_rate;
	uint32_t clock_source_speed;
}USART_Config;


void configureUSARTDevice (usart_device device, USART_Config * config);
void enableUSARTDevice (usart_device device);
void disableUSARTDevice (usart_device device, bool use_dma_flag);
void dmaEnableTransmit (usart_device device);
void dmaEnableRecieve (usart_device device);
void dmaDisableTransmit (usart_device device);
void dmaDisableRecieve (usart_device device);
void transmit_packet (usart_device device, uint8_t * packet, uint32_t length);
void recieve_packet (usart_device device, uint8_t * packet, uint32_t length);
void DMA_transmit_setup (usart_device device, uint8_t * packet, uint32_t length, DMA_Stream_Config * dmaStreamConfig);
void DMA_recieve_setup (usart_device device, uint8_t * packet, uint32_t length, DMA_Stream_Config * dmaStreamConfig);
uint32_t checkUSARTDeviceFlags (usart_device device, uint32_t flagsCheckMask);
void clearUSARTDeviceFlags (usart_device device, uint32_t flagsClearMask);

#endif /* USART_DRIVER_H_ */
