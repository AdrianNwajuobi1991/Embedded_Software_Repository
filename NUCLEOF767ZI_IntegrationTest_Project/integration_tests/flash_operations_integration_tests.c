/*
 * flash_operations_integration_tests.c
 *
 *  Created on: Oct 25, 2024
 *      Author: root
 */

#include "FLASH_Dependency_Injection.h"
#include "FLASH_Driver.h"
#include <stdint.h>
#include <stdbool.h>
#include "gpio_integration_test.h"

static flash_device flashDevice = 0;


void test_flash_erase_and_write (void) {
	uint8_t status = false;
	volatile uint8_t * flashSectorElevenPtr = (volatile uint8_t * )0x081C0000;
	uint32_t array_one [200];
	uint32_t array_two [200];
	uint8_t * array_one_ptr = (uint8_t *)array_one;
	uint8_t * array_two_ptr = (uint8_t *)array_two;
	for (uint32_t index = 0; index < 200; index++) {
		array_one[index] = index;
		array_two[index] = 2*index+1;
	}

	flashSectorErase (flashDevice, 11);
	flashWriteData (flashDevice, array_one, sizeof(array_one), flashSectorElevenPtr);

	for (uint32_t index = 0; index < 200; index++) {
		if (array_one_ptr[index] == flashSectorElevenPtr[index]) {
			status = true;
		}else{
			status = false;
			break;
		}
	}
	if (status == true) {
		turn_on_RED_LED_PORTB();
	}
	status = false;

	flashSectorErase (flashDevice, 11);
	flashWriteData (flashDevice, array_two, sizeof(array_two), flashSectorElevenPtr);

	for (uint32_t index = 0; index < 200; index++) {
		if (array_two_ptr[index] == flashSectorElevenPtr[index]) {
			status = true;
		}else{
			status = false;
			break;
		}
	}
	if (status == true) {
		turn_on_GREEN_LED_PORTB();
	}
	flashSectorErase (flashDevice, 11);
	lockFlashControlRegister (flashDevice);
}

void setup_flash_device (void) {
	flashDevice = getFlashDeviceInstance();
	unlockFlashControlRegister (flashDevice);
	setFlashParallelism (flashDevice, X32);
}
