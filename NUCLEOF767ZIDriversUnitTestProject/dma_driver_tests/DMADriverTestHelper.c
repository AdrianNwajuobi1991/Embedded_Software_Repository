/*
 * DMADriverTestHelper.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */
#include "DMADriverTestHelper.h"
#include "STM32F767ZI_DMAStreamDeviceDriverLayout.h"
#include "register_bit_utils.h"

void setDMADeviceLISRValue (dma_device device) {

}

void setDMADeviceHISRValue (dma_device device) {

}

void setDMADeviceLIFCRValue (dma_device device) {

}

void setDMADeviceHIFCRValue (dma_device device) {

}

uint32_t getDMADeviceLISRValue (dma_device device) {

}

uint32_t getDMADeviceHISRValue (dma_device device) {

}

uint32_t getDMADeviceLIFCRValue (dma_device device) {

}

uint32_t getDMADeviceHIFCRValue (dma_device device) {

}

uint32_t getDMAStreamCRValue (dma_stream_device device) {
	return registerGetValue (&device->CR);
}

uint32_t getDMAStreamNDTRValue (dma_stream_device device) {
	return registerGetValue (&device->NDTR);
}

uint32_t getDMAStreamPARValue (dma_stream_device device) {
	return registerGetValue (&device->PAR);
}

uint32_t getDMAStreamM0ARValue (dma_stream_device device) {
	return registerGetValue (&device->M0AR);
}

uint32_t getDMAStreamM1ARValue (dma_stream_device device) {
	return registerGetValue (&device->M1AR);
}

uint32_t getDMAStreamFCRValue (dma_stream_device device) {
	return registerGetValue (&device->FCR);
}
