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

static DMA_Stream_TypeDef_t dmaStreams[3];
static DMA_TypeDef_t dmaDevices[2];

dma_stream_device getDMAStreamInstance(int dmaStreamNumber) {

	dmaStreams[dmaStreamNumber].FCR = 0x21;
	return &dmaStreams[dmaStreamNumber];

}

void enableDMAStream (dma_stream_device device) {
	registerSetBit(&device->CR, 0);
}

void disableDMAStream (dma_stream_device device) {
	registerClearBit(&device->CR, 0);
}

void Initialize_DMA2 (void) {

}

dma_device getDMADeviceInstance(int dmaDeviceInstance) {

}

void DMAStreamDeviceCleanUp(dma_stream_device device, DMA_Stream_Config * dmaStreamConfig) {
	memset(device, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_TypeDef_t));
	device->FCR = 0x21;
}

void DMADeviceCleanUp(dma_device device) {

}

