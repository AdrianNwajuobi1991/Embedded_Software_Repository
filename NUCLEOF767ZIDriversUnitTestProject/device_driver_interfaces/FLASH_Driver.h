/*
 * FLASH_Driver.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct FLASH_TypeDef_t * flash_device;

enum{
	FLASH_DEFAULT_SETTING
};

enum{
	X8=0b00, X16=0b01, X32=0b10, X64=0b11
};

enum{
	OPERR=1, WRPERR=4, PGAERR=5, PGPERR=6, ERSERR=7
};

enum {
	ERRIE=25
};

void flashInterruptConfiguration (flash_device device, uint8_t interruptSetting);

void unlockFlashControlRegister (flash_device device);

void lockFlashControlRegister (flash_device device);

void unlockFlashOptionRegister (flash_device device);

void lockFlashOptionRegister (flash_device device);

void setFlashParallelism (flash_device device, uint8_t parallelismLevel);

void flashSectorErase (flash_device device, uint8_t sectorNumber);

void flashWriteData (flash_device device, void * data, uint32_t size, volatile uint8_t * flashMemoryAddress);

bool checkFlashOperationError (flash_device device, uint8_t errorType);


#endif /* FLASH_DRIVER_H_ */
