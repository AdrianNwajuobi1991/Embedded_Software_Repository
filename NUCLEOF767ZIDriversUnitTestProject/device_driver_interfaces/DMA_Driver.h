/*
 * DMA_Driver.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef DMA_DRIVER_H_
#define DMA_DRIVER_H_

#include <stdint.h>

typedef struct DMA_Stream_TypeDef_t * dma_stream_device;

typedef struct DMA_TypeDef_t * dma_device;

enum{
	DMA_DEFAULT_SETTING
};

enum{
	PERIPH_TO_MEM=0, MEM_TO_PERIPH=1, MEM_TO_MEM=2
};

enum {
	BYTE=0, HALF_WORD=1, WORD=2
};

enum {
	LOW_PRIORITY=0, MEDIUM_PRIORITY=1, HIGH_PRIORITY=2, VERY_HIGH_PRIORITY=3
};

enum {
	SINGLE_TRANSFER=0, INCR4, INCR8, INCR16
};

enum {
	CHANNEL_ONE=1, CHANNEL_TWO=2, CHANNEL_FOUR=4
};

enum {
	QUARTER_LEVEL_FIFO=0, HALF_LEVEL_FIFO=1, THREE_QUARTER_LEVEL_FIFO=2, FULL_LEVEL_FIFO=3
};

enum {
	DISABLE_FIFO=0, ENABLE_FIFO=1
};

enum {
	FIXED=0, INCREMENT=1
};

enum {
	DISABLE_CIRCULAR_MODE=0, ENABLE_CIRCULAR_MODE=1
};

enum {
	DISABLE_DOUBLE_BUFFER_MODE=0, ENABLE_DOUBLE_BUFFER_MODE=1
};

typedef struct DMA_Stream_Config {
	uint8_t transferDirection;
	uint16_t numberOfDataItems;
	uint32_t sourceAddress;
	uint32_t destinationAddress;
	uint8_t dataItemSize;
	uint8_t priorityLevel;
	uint8_t memoryBurstSize;
	uint8_t peripheralBurstSize;
	uint8_t memoryIncrementMode;
	uint8_t peripheralIncrementMode;
	uint8_t channelSelection;
	uint8_t fifoSetting;
	uint8_t fifoLevel;
	uint8_t circularMode;
	uint8_t doubleBufferMode;
}DMA_Stream_Config;

void disableDMAStream (dma_stream_device device);

void enableDMAStream (dma_stream_device device);

uint32_t readDMAStatusRegisterFlag (dma_device dmaDevice, uint8_t flagBitPosition);

void configureDMAStream(dma_stream_device dmaStream, dma_device dmaDevice, DMA_Stream_Config * config);

#endif /* DMA_DRIVER_H_ */
