/*
 * DMADriverTest.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */
#include "unity.h"
#include "DMA_Driver.h"
#include "DMADriverTest.h"
#include "DMADriverTestHelper.h"
#include <string.h>

extern dma_stream_device dmaStream;
extern dma_device dmaDevice;


void test_DMA_STREAM_Device_Default_State (void) {
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamCRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamNDTRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamPARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamM0ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamM1ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000021, getDMAStreamFCRValue(dmaStream));
}

void test_PERIPHERAL_TO_MEMORY_Transfer_4_NDT_PSIZE_AND_MSIZE_OF_2_BYTES_FIFO_ENABLED (void) {
	DMA_Stream_Config dmaStreamConfig;
	memset(&dmaStreamConfig, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_Config));
	dmaStreamConfig.transferDirection = PERIPH_TO_MEM;
	dmaStreamConfig.numberOfDataItems = 4;
	dmaStreamConfig.sourceAddress = 0x4000084C;
	dmaStreamConfig.destinationAddress = 0x20005000;
	dmaStreamConfig.dataItemSize = HALF_WORD;
	dmaStreamConfig.priorityLevel = HIGH_PRIORITY;
	dmaStreamConfig.memoryBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig.peripheralBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig.memoryIncrementMode = INCREMENT;
	dmaStreamConfig.peripheralIncrementMode = FIXED;
	dmaStreamConfig.channelSelection = CHANNEL_TWO;
	dmaStreamConfig.fifoLevel = HALF_LEVEL_FIFO;
	dmaStreamConfig.fifoSetting = ENABLE_FIFO;
	dmaStreamConfig.circularMode = DISABLE_CIRCULAR_MODE;
	dmaStreamConfig.doubleBufferMode = DISABLE_DOUBLE_BUFFER_MODE;
	configureDMAStream(dmaStream, dmaDevice, &dmaStreamConfig);
	TEST_ASSERT_EQUAL_HEX32(0x04022C00, getDMAStreamCRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000004, getDMAStreamNDTRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x4000084C, getDMAStreamPARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x20005000, getDMAStreamM0ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamM1ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000025, getDMAStreamFCRValue(dmaStream));
}

void test_MEMORY_TO_PERIPHERAL_Transfer_4_NDT_PSIZE_AND_MSIZE_OF_2_BYTES_FIFO_ENABLED (void) {
	DMA_Stream_Config dmaStreamConfig;
	memset(&dmaStreamConfig, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_Config));
	dmaStreamConfig.transferDirection = MEM_TO_PERIPH;
	dmaStreamConfig.numberOfDataItems = 4;
	dmaStreamConfig.sourceAddress = 0x20005000;
	dmaStreamConfig.destinationAddress = 0x4000084C;
	dmaStreamConfig.dataItemSize = HALF_WORD;
	dmaStreamConfig.priorityLevel = HIGH_PRIORITY;
	dmaStreamConfig.memoryBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig.peripheralBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig.memoryIncrementMode = INCREMENT;
	dmaStreamConfig.peripheralIncrementMode = FIXED;
	dmaStreamConfig.channelSelection = CHANNEL_TWO;
	dmaStreamConfig.fifoLevel = HALF_LEVEL_FIFO;
	dmaStreamConfig.fifoSetting = ENABLE_FIFO;
	dmaStreamConfig.circularMode = DISABLE_CIRCULAR_MODE;
	dmaStreamConfig.doubleBufferMode = DISABLE_DOUBLE_BUFFER_MODE;
	configureDMAStream(dmaStream, dmaDevice, &dmaStreamConfig);
	TEST_ASSERT_EQUAL_HEX32(0x04022C40, getDMAStreamCRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000004, getDMAStreamNDTRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x4000084C, getDMAStreamPARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x20005000, getDMAStreamM0ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamM1ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000025, getDMAStreamFCRValue(dmaStream));
}

void test_MEMORY_TO_MEMORY_Transfer_4_NDT_PSIZE_AND_MSIZE_OF_2_BYTES_FIFO_ENABLED (void) {
	DMA_Stream_Config dmaStreamConfig;
	memset(&dmaStreamConfig, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_Config));
	dmaStreamConfig.transferDirection = MEM_TO_MEM;
	dmaStreamConfig.numberOfDataItems = 4;
	dmaStreamConfig.sourceAddress = 0x20005000;
	dmaStreamConfig.destinationAddress = 0x20015700;
	dmaStreamConfig.dataItemSize = HALF_WORD;
	dmaStreamConfig.priorityLevel = MEDIUM_PRIORITY;
	dmaStreamConfig.memoryBurstSize = INCR4;
	dmaStreamConfig.peripheralBurstSize = INCR8;
	dmaStreamConfig.channelSelection = CHANNEL_ONE;
	dmaStreamConfig.fifoLevel = HALF_LEVEL_FIFO;
	dmaStreamConfig.fifoSetting = ENABLE_FIFO;
	dmaStreamConfig.circularMode = DISABLE_CIRCULAR_MODE;
	dmaStreamConfig.doubleBufferMode = DISABLE_DOUBLE_BUFFER_MODE;
	configureDMAStream(dmaStream, dmaDevice, &dmaStreamConfig);
	TEST_ASSERT_EQUAL_HEX32(0x02C12E80, getDMAStreamCRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000004, getDMAStreamNDTRValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x20005000, getDMAStreamPARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x20015700, getDMAStreamM0ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getDMAStreamM1ARValue(dmaStream));
	TEST_ASSERT_EQUAL_HEX32(0x00000025, getDMAStreamFCRValue(dmaStream));
}

