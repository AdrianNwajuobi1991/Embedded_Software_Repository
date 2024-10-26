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
#include "stm32f7xx.h"

#define BSY_BITPOS		16


flash_device getFlashDeviceInstance (void) {
	return (flash_device)FLASH_R_BASE;
}

void FlashDeviceInstanceCleanUp (void) {

}

void DSB_Instruction (void) {
	__asm volatile( "DSB" );
}

void waitForFlashBusy(flash_device device) {
	while (registerTestBitPosition (&device->SR, BSY_BITPOS) == BIT_SET) {}
}
