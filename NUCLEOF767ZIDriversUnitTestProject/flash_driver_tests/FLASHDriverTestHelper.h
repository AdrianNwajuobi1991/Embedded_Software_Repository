/*
 * FLASHDriverTestHelper.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef FLASHDRIVERTESTHELPER_H_
#define FLASHDRIVERTESTHELPER_H_

#include <stdint.h>
#include "FLASH_Driver.h"

uint32_t getFlashACRRValue (flash_device device);
uint32_t getFlashKEYRValue (flash_device device);
uint32_t getFlashOPTKEYRRValue (flash_device device);
uint32_t getFlashSRRValue (flash_device device);
uint32_t getFlashCRRValue (flash_device device);
uint32_t getFlashOPTCRRValue (flash_device device);
uint32_t getFlashOPTCR1RValue (flash_device device);

#endif /* FLASHDRIVERTESTHELPER_H_ */
