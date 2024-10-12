/*
 * dma_integration_test.c
 *
 *  Created on: Sep 7, 2024
 *      Author: root
 */

#include "dma_integration_test.h"
#include "DMA_Driver.h"
#include "DMA_Dependency_Injection.h"
#include "timers_integration_test.h"
#include <string.h>
#include "gpio_integration_test.h"

static dma_stream_device dmaStream;
static dma_device dmaDevice;


void setup_dma_integration_test (void) {
	Initialize_DMA2();
}

void dma_memory_transfer_test (void) {
	dmaStream = getDMAStreamInstance(DMA_STREAM_0);
	dmaDevice = getDMADeviceInstance(DMA_2);

	uint16_t sourceData [] = {170, 110, 200, 450};
	uint16_t destData [] = {0};
	DMA_Stream_Config dmaStreamConfig;
	memset(&dmaStreamConfig, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_Config));
	dmaStreamConfig.transferDirection = MEM_TO_MEM;
	dmaStreamConfig.numberOfDataItems = 4;
	dmaStreamConfig.sourceAddress = (uint32_t)sourceData;
	dmaStreamConfig.destinationAddress = (uint32_t)destData;
	dmaStreamConfig.dataItemSize = HALF_WORD;
	dmaStreamConfig.priorityLevel = MEDIUM_PRIORITY;
	dmaStreamConfig.memoryBurstSize = INCR4;
	dmaStreamConfig.peripheralBurstSize = INCR8;
	dmaStreamConfig.channelSelection = CHANNEL_ONE;
	dmaStreamConfig.fifoLevel = HALF_LEVEL_FIFO;
	dmaStreamConfig.fifoSetting = ENABLE_FIFO;

	configureDMAStream(dmaStream, dmaDevice, &dmaStreamConfig);
	enableDMAStream(dmaStream);
	delay(100);

	if (destData[0] == 170 && destData[1] == 110 && destData[2] == 200 && destData[3] == 450) {
		turn_on_GREEN_LED_PORTB ();
	}
}
