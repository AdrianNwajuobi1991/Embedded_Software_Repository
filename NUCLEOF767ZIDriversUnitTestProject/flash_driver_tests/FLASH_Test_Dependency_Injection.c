/*
 * FLASH_Test_Dependency_Injection.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "FLASH_Dependency_Injection.h"
#include "STM32F767ZI_FLASHDeviceDriverLayout.h"
#include <string.h>
#include "register_bit_utils.h"

static FLASH_TypeDef_t flashDevice;


flash_device getFlashDeviceInstance (void) {
	flash_device device = &flashDevice;
	memset(device, 0, sizeof(FLASH_TypeDef_t));
	device->CR = 0x80000000;
	device->OPTCR = 0xFFFFAAFD;
	device->OPTCR1 = 0x00400080;
	return device;
}

void FlashDeviceInstanceCleanUp (void) {
	flash_device device = &flashDevice;
	memset(device, 0, sizeof(FLASH_TypeDef_t));
	device->CR = 0x80000000;
	device->OPTCR = 0xFFFFAAFD;
	device->OPTCR1 = 0x00400080;
}

void DSB_Instruction (void) {

}

void waitForFlashBusy(flash_device device) {
	registerSetBit (&device->SR, 1);
}
