/*
 * DMADriverTestHelper.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef DMADRIVERTESTHELPER_H_
#define DMADRIVERTESTHELPER_H_

#include "DMA_Driver.h"
#include <stdint.h>

void setDMADeviceLISRValue (dma_device device);
void setDMADeviceHISRValue (dma_device device);
void setDMADeviceLIFCRValue (dma_device device);
void setDMADeviceHIFCRValue (dma_device device);

uint32_t getDMADeviceLISRValue (dma_device device);
uint32_t getDMADeviceHISRValue (dma_device device);
uint32_t getDMADeviceLIFCRValue (dma_device device);
uint32_t getDMADeviceHIFCRValue (dma_device device);

uint32_t getDMAStreamCRValue (dma_stream_device device);
uint32_t getDMAStreamNDTRValue (dma_stream_device device);
uint32_t getDMAStreamPARValue (dma_stream_device device);
uint32_t getDMAStreamM0ARValue (dma_stream_device device);
uint32_t getDMAStreamM1ARValue (dma_stream_device device);
uint32_t getDMAStreamFCRValue (dma_stream_device device);


#endif /* DMADRIVERTESTHELPER_H_ */
