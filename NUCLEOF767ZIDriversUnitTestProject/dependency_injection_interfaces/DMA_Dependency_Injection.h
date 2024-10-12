/*
 * DMA_Dependency_Injection.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef DMA_DEPENDENCY_INJECTION_H_
#define DMA_DEPENDENCY_INJECTION_H_

#include "DMA_Driver.h"

enum{
	DMA_STREAM_0, DMA_STREAM_3=3, DMA_STREAM_4=4, DMA_STREAM_6=6, DMA_STREAM_7=7
};

enum{
	DMA_1, DMA_2
};

dma_stream_device getDMAStreamInstance(int dmaStreamNumber);

dma_device getDMADeviceInstance(int dmaDeviceInstance);

void Initialize_DMA2 (void);

void Initialize_DMA1 (void);

void DMAStreamDeviceCleanUp(dma_stream_device device, DMA_Stream_Config * dmaStreamConfig);

void DMADeviceCleanUp(dma_device device);


#endif /* DMA_DEPENDENCY_INJECTION_H_ */
