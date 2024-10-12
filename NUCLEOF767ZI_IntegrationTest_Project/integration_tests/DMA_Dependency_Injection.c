/*
 * DMA_Test_Dependency_Injection.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "STM32F767ZI_DMAStreamDeviceDriverLayout.h"
#include "DMA_Dependency_Injection.h"
#include <string.h>
#include "register_bit_utils.h"
#include "stm32f767xx.h"

dma_stream_device getDMAStreamInstance(int dmaStreamNumber) {

	if (dmaStreamNumber == DMA_STREAM_0) {
		return (dma_stream_device)DMA2_Stream0_BASE;
	}
	if (dmaStreamNumber == DMA_STREAM_6) {
		return (dma_stream_device)DMA1_Stream6_BASE;
	}
	if (dmaStreamNumber == DMA_STREAM_7) {
		return (dma_stream_device)DMA1_Stream7_BASE;
	}
	if (dmaStreamNumber == DMA_STREAM_3) {
		return (dma_stream_device)DMA1_Stream3_BASE;
	}
	if (dmaStreamNumber == DMA_STREAM_4) {
		return (dma_stream_device)DMA1_Stream4_BASE;
	}

}

void enableDMAStream (dma_stream_device device) {
	registerSetBit(&device->CR, 0);
}

void disableDMAStream (dma_stream_device device) {
	registerClearBit(&device->CR, 0);
	while(registerTestBitPosition (&device->CR, 0) == BIT_SET){}
}

void Initialize_DMA2 (void) {
	RCC->AHB1ENR |= (1 << 22);
}

void Initialize_DMA1 (void) {
	RCC->AHB1ENR |= (1 << 21);
}


dma_device getDMADeviceInstance(int dmaDeviceInstance) {
	if (dmaDeviceInstance == DMA_2) {
		return (dma_device)DMA2_BASE;
	}
	if (dmaDeviceInstance == DMA_1) {
		return (dma_device)DMA1_BASE;
	}
}

void DMAStreamDeviceCleanUp(dma_stream_device device, DMA_Stream_Config * dmaStreamConfig) {

}

void DMADeviceCleanUp(dma_device device) {

}

