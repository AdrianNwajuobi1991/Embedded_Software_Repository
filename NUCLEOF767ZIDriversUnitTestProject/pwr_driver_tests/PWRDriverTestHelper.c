/*
 * PWRDriverTestHelper.c
 *
 *  Created on: Nov 4, 2024
 *      Author: root
 */

#include "PWRDriverTestHelper.h"
#include "STM32F767ZI_PWRControlDeviceDriverLayout.h"
#include "register_bit_utils.h"

uint32_t getPWR_CR1RValue (power_control_device device) {
	return registerGetValue(&device->CR1);
}
