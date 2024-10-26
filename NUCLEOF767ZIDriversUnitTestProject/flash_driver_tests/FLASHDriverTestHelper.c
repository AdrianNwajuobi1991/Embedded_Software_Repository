/*
 * FLASHTestHelper.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "FLASHDriverTestHelper.h"
#include "register_bit_utils.h"
#include "STM32F767ZI_FLASHDeviceDriverLayout.h"


uint32_t getFlashACRRValue (flash_device device) {
	return registerGetValue(&device->ACR);
}

uint32_t getFlashKEYRValue (flash_device device) {
	return registerGetValue(&device->KEYR);
}

uint32_t getFlashOPTKEYRRValue (flash_device device) {
	return registerGetValue(&device->OPTKEYR);
}

uint32_t getFlashSRRValue (flash_device device) {
	return registerGetValue(&device->SR);
}

uint32_t getFlashCRRValue (flash_device device) {
	return registerGetValue(&device->CR);
}

uint32_t getFlashOPTCRRValue (flash_device device) {
	return registerGetValue(&device->OPTCR);
}

uint32_t getFlashOPTCR1RValue (flash_device device) {
	return registerGetValue(&device->OPTCR1);
}
