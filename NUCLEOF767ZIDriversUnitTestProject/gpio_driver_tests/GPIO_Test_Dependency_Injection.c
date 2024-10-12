/*
 * GPIO_Test_Dependency_Injection.c
 *
 *  Created on: Aug 1, 2024
 *      Author: root
 */

#include "GPIO_Dependency_Injection.h"
#include "GPIODriver.h"
#include "STM32F767ZIGPIODeviceLayout.h"
#include "GPIO_Device_Common.h"


#define MAX_GPIO_INSTANCE	5


static GPIO_TypeDef_t gpioDevices[MAX_GPIO_INSTANCE];



gpio_device getGPIODeviceInstance (int deviceInstance) {
	if (deviceInstance == PORTA) {
		gpioDevices[deviceInstance].MODER = 0xA8000000;
	}
	if (deviceInstance == PORTB) {
		gpioDevices[deviceInstance].MODER = 0x00000280;
	}
	return &gpioDevices[deviceInstance];
}

void GPIODeviceCleanUp (gpio_device device, GPIOPortConfiguration* config) {
	for (int index = 0; index < 5; index++) {
		if (&gpioDevices[index] == device) {
			if (index == PORTA) {
				device->MODER = 0xA8000000;
				device->OSPEEDR = 0x0C000000;
				device->PUPDR = 0x64000000;
			}
			if (index == PORTB) {
				device->MODER = 0x00000280;
				device->OSPEEDR = 0x000000C0;
				device->PUPDR = 0x00000100;
			}
			device->AFR[0] = 0;
			device->AFR[1] = 0;
			device->OTYPER = 0;
			device->BSRR = 0;
			device->IDR = 0;
			device->ODR = 0;
		}
	}
}
