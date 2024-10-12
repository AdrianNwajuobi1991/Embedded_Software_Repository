/*
 * STM32F767ZI_DMA_Driver.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */
#include "DMA_Driver.h"
#include "DMA_Dependency_Injection.h"
#include "register_bit_utils.h"
#include "STM32F767ZI_DMAStreamDeviceDriverLayout.h"

static void clearDMAStatusRegisterFlags (dma_device dmaDevice, uint32_t bitPositionsMask);

uint32_t readDMAStatusRegisterFlag (dma_device dmaDevice, uint8_t flagBitPosition) {
	uint32_t status;
	if (flagBitPosition >= 0 && flagBitPosition <= 3) {
		status = registerTestBitPosition (&dmaDevice->LISR, flagBitPosition);
	}
	if (flagBitPosition >= 4 && flagBitPosition <= 7) {
		status = registerTestBitPosition (&dmaDevice->HISR, flagBitPosition);
	}
	return status;
}

void configureDMAStream(dma_stream_device dmaStream, dma_device dmaDevice, DMA_Stream_Config * config) {
	clearDMAStatusRegisterFlags (dmaDevice, 0xFFFFFFFF);
	clearDMAStatusRegisterFlags (dmaDevice, 0xFFFFFFFF);

	registerOverwriteValue (&dmaStream->CR, 0);
	registerSetValueInBitPosition (&dmaStream->CR, config->transferDirection, 6);
	if (config->transferDirection == MEM_TO_MEM) {
		registerSetBit(&dmaStream->CR, 9);
		registerSetBit(&dmaStream->CR, 10);
	}else{
		registerSetValueInBitPosition(&dmaStream->CR, config->peripheralIncrementMode, 9);
		registerSetValueInBitPosition(&dmaStream->CR, config->memoryIncrementMode, 10);
	}

	registerSetValueInBitPosition(&dmaStream->CR, config->dataItemSize, 11);
	registerSetValueInBitPosition(&dmaStream->CR, config->dataItemSize, 13);

	registerSetValueInBitPosition (&dmaStream->CR, config->priorityLevel, 16);


	registerSetValueInBitPosition (&dmaStream->CR, config->peripheralBurstSize, 21);
	registerSetValueInBitPosition (&dmaStream->CR, config->memoryBurstSize, 23);

	registerSetValueInBitPosition (&dmaStream->CR, config->channelSelection, 25);

	registerOverwriteValue (&dmaStream->NDTR, config->numberOfDataItems);

	if (config->transferDirection == MEM_TO_MEM || config->transferDirection == PERIPH_TO_MEM) {
		registerOverwriteValue (&dmaStream->PAR, config->sourceAddress);
		registerOverwriteValue (&dmaStream->M0AR, config->destinationAddress);
	}
	if (config->transferDirection == MEM_TO_PERIPH) {
		registerOverwriteValue (&dmaStream->PAR, config->destinationAddress);
		registerOverwriteValue (&dmaStream->M0AR, config->sourceAddress);
	}

	if (config->doubleBufferMode != DISABLE_DOUBLE_BUFFER_MODE) {
		registerSetValueInBitPosition (&dmaStream->CR, config->doubleBufferMode, 18);
	}

	if (config->circularMode != DISABLE_CIRCULAR_MODE) {
		registerSetValueInBitPosition (&dmaStream->CR, config->circularMode, 8);
	}

	registerOverwriteValue (&dmaStream->FCR, 0x21);
	if (config->fifoSetting != DISABLE_FIFO) {
		registerSetValueInBitPosition (&dmaStream->FCR, config->fifoSetting, 2);
		registerSetValueInBitPosition (&dmaStream->FCR, config->fifoLevel, 0);
	}
}

static void clearDMAStatusRegisterFlags (dma_device dmaDevice, uint32_t bitPositionsMask) {
	registerOverwriteValue (&dmaDevice->LIFCR, bitPositionsMask);
	registerOverwriteValue (&dmaDevice->HIFCR, bitPositionsMask);
}
