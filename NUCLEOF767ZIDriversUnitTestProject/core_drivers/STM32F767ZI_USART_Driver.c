/*
 * STM32F767ZI_USART_Driver.c
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */
#include "USART_Driver.h"
#include "STM32F767ZI_USARTDeviceDriverLayout.h"
#include "USART_Dependency_Injection.h"
#include "DMA_Dependency_Injection.h"
#include "register_bit_utils.h"
#include "DMA_Driver.h"
#include <stdbool.h>
#include <string.h>


#define UE_BITPOS		0
#define RE_BITPOS		2
#define TE_BITPOS		3
#define DMAT_BITPOS		7
#define DMAR_BITPOS		6
#define TCCF_BITPOS		6
#define TXEIE_BITPOS	7
#define RXNEIE_BITPOS	5
#define EIE_BITPOS		0


uint32_t checkUSARTDeviceFlags (usart_device device, uint32_t flagsCheckMask) {
	return registerGetMaskBits (&device->ISR, flagsCheckMask);
}

void clearUSARTDeviceFlags (usart_device device, uint32_t flagsClearMask) {
	device->ICR |= flagsClearMask;
}

void configureUSARTDevice (usart_device device, USART_Config * config) {
	device->BRR = 0;
	if (config->oversampling_mode == OVERSAMPLE_16X) {
		uint32_t USARTDIV = (uint32_t)((config->clock_source_speed/config->baud_rate)+1.0);
		device->BRR = USARTDIV;
	}
	if (config->oversampling_mode == OVERSAMPLE_8X) {
		uint32_t USARTDIV = (uint32_t)(((2 * config->clock_source_speed)/config->baud_rate)+1.0);
		uint32_t USARTDIV_3_0 = (USARTDIV & 0xF);
		uint32_t USARTDIV_15_4 = (USARTDIV >> 4);
		device->BRR |= USARTDIV_3_0 >> 1; //BRR[2:0]
		device->BRR &= ~(1 << 3); //BRR[3] = 0
		device->BRR |= USARTDIV_15_4 << 4; //BRR[15:4]
	}
	if (config->use_error_interrupts == true) {
		device->CR3 |= (1 << EIE_BITPOS);
	}
	if (config->use_rx_interrupt == true) {
		device->CR1 |= (1 << RXNEIE_BITPOS);
	}
	if (config->use_tx_interrupt == true) {
		device->CR1 |= (1 << TXEIE_BITPOS);
	}
}

void dmaEnableTransmit (usart_device device) {
	device->CR3 |= (1 << DMAT_BITPOS);
}

void dmaEnableRecieve (usart_device device) {
	device->CR3 |= (1 << DMAR_BITPOS);
}

void dmaDisableTransmit (usart_device device) {
	device->CR3 &= ~(1 << DMAT_BITPOS);
}

void dmaDisableRecieve (usart_device device) {
	device->CR3 &= ~(1 << DMAR_BITPOS);
}

void enableUSARTDevice (usart_device device) {
	registerSetBit(&device->CR1, UE_BITPOS);
	registerSetBit(&device->CR1, RE_BITPOS);
	registerSetBit(&device->CR1, TE_BITPOS);
}

void disableUSARTDevice (usart_device device, bool use_dma_flag) {
	Wait_For_TC_Flag(device);
	if (use_dma_flag == false) {
		registerClearBit(&device->CR1, UE_BITPOS);
		registerClearBit(&device->CR1, RE_BITPOS);
		registerClearBit(&device->CR1, TE_BITPOS);
	}
}

void DMA_transmit_setup (usart_device device, uint8_t * packet, uint32_t length, DMA_Stream_Config * dmaStreamConfig) {
	memset(dmaStreamConfig, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_Config));
	dmaStreamConfig->transferDirection = MEM_TO_PERIPH;
	dmaStreamConfig->numberOfDataItems = length;
	dmaStreamConfig->sourceAddress = (uint32_t)packet;
	dmaStreamConfig->destinationAddress = (uint32_t)&device->TDR;
	dmaStreamConfig->dataItemSize = BYTE;
	dmaStreamConfig->memoryBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig->peripheralBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig->memoryIncrementMode = INCREMENT;
	dmaStreamConfig->peripheralIncrementMode = FIXED;

	registerSetBit(&device->ICR, TCCF_BITPOS);
}

void DMA_recieve_setup (usart_device device, uint8_t * packet, uint32_t length, DMA_Stream_Config * dmaStreamConfig) {
	memset(dmaStreamConfig, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_Config));
	dmaStreamConfig->transferDirection = PERIPH_TO_MEM;
	dmaStreamConfig->numberOfDataItems = length;
	dmaStreamConfig->sourceAddress = (uint32_t)&device->RDR;
	dmaStreamConfig->destinationAddress = (uint32_t)packet;
	dmaStreamConfig->dataItemSize = BYTE;
	dmaStreamConfig->memoryBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig->peripheralBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig->memoryIncrementMode = INCREMENT;
	dmaStreamConfig->peripheralIncrementMode = FIXED;
}

void transmit_packet (usart_device device, uint8_t * packet, uint32_t length) {
	uint32_t count = 0;
	while (count < length) {
		Wait_For_TXE_Flag(device);
		*(volatile uint8_t *)&device->TDR = packet[count];
		count++;
	}
	Wait_For_TC_Flag(device);
}

void recieve_packet (usart_device device, uint8_t * packet, uint32_t length) {
	uint32_t count = 0;
	while (count < length) {
		Wait_For_RXNE_Flag(device);
		packet[count] = *(volatile uint8_t *)&device->RDR;
		count++;
	}
}

