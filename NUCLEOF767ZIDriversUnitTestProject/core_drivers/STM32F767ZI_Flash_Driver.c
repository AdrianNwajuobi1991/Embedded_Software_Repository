/*
 * STM32F767ZI_Flash_Driver.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "FLASH_Driver.h"
#include "STM32F767ZI_FLASHDeviceDriverLayout.h"
#include "register_bit_utils.h"
#include "FLASH_Dependency_Injection.h"
#include <stdbool.h>


#define LOCK_BITPOS		31
#define PSIZE_BITPOS	8
#define SER_BITPOS		1
#define SNB_BITPOS		3
#define STRT_BITPOS		16
#define PG_BITPOS		0
#define OPTLOCK_BITPOS	0

static uint8_t parallelismValue = X8;

void unlockFlashControlRegister (flash_device device) {
	waitForFlashBusy(device);
	registerOverwriteValue (&device->KEYR, 0x45670123);
	waitForFlashBusy(device);
	registerOverwriteValue (&device->KEYR, 0xCDEF89AB);
	waitForFlashBusy(device);
}

void lockFlashControlRegister (flash_device device) {
	registerSetBit (&device->CR, LOCK_BITPOS);
}

void unlockFlashOptionRegister (flash_device device) {
	waitForFlashBusy(device);
	registerOverwriteValue (&device->OPTKEYR, 0x08192A3B);
	waitForFlashBusy(device);
	registerOverwriteValue (&device->OPTKEYR, 0x4C5D6E7F);
	waitForFlashBusy(device);
}

void lockFlashOptionRegister (flash_device device) {
	registerSetBit (&device->OPTCR, OPTLOCK_BITPOS);
}

void setFlashParallelism(flash_device device, uint8_t parallelismLevel) {
	registerSetValueInBitPosition (&device->CR, parallelismLevel, PSIZE_BITPOS);
	parallelismValue = parallelismLevel;
}

void flashSectorErase (flash_device device, uint8_t sectorNumber) {
	uint32_t SNB_Mask = ~(0x1F << SNB_BITPOS);
	waitForFlashBusy(device);
	device->CR &= SNB_Mask;
	registerSetBit (&device->CR, SER_BITPOS);
	registerSetValueInBitPosition (&device->CR, sectorNumber, SNB_BITPOS);
	registerSetBit (&device->CR, STRT_BITPOS);
	waitForFlashBusy(device);
}

void flashInterruptConfiguration (flash_device device, uint8_t interruptSetting) {
	registerSetBit (&device->CR, interruptSetting);
}

void flashWriteData (flash_device device, void * data, uint32_t size, volatile uint8_t * flashMemoryAddress) {
	waitForFlashBusy(device);
	registerSetBit (&device->CR, PG_BITPOS);
	if (parallelismValue == X8 && data != 0 && flashMemoryAddress != 0) {
		uint8_t * dataPtr = (uint8_t *)data;
		for (uint32_t index = 0; index < size; index ++) {
			flashMemoryAddress[index] = dataPtr[index];
			DSB_Instruction();
			waitForFlashBusy(device);
		}
	}
	if (parallelismValue == X32 && data != 0 && flashMemoryAddress != 0) {
		uint32_t * dataPtr = (uint32_t *)data;
		volatile uint32_t * flashMemPtr = (volatile uint32_t *)flashMemoryAddress;
		size = size/sizeof(uint32_t);
		for (uint32_t index = 0; index < size; index ++) {
			flashMemPtr[index] = dataPtr[index];
			DSB_Instruction();
			waitForFlashBusy(device);
		}
	}
	waitForFlashBusy(device);
}

bool checkFlashOperationError (flash_device device, uint8_t errorType) {
	if (registerTestBitPosition (&device->SR, errorType) == BIT_SET) {
		registerClearBit (&device->SR, errorType);
		return true;
	}
	return false;
}
