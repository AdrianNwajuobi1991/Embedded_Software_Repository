/*
 * GPIODriverTestHelper.c
 *
 *  Created on: May 10, 2024
 *      Author: root
 */
#include "GPIODriverTestHelper.h"

#include "register_bit_utils.h"
#include <stdint.h>
#include "GPIO_Dependency_Injection.h"
#include "GPIODriver.h"
#include "STM32F767ZIGPIODeviceLayout.h"



unsigned int getGPIODeviceMODERegisterValue(gpio_device device) {
	return registerGetValue(&device->MODER);
}

unsigned int getGPIODeviceOutputTypeRegisterValue(gpio_device device) {
	return registerGetValue(&device->OTYPER);
}

unsigned int getGPIODeviceOutputSpeedRegisterValue(gpio_device device) {
	return registerGetValue(&device->OSPEEDR);
}

unsigned int getGPIODevicePUPDRegisterValue(gpio_device device) {
	return registerGetValue(&device->PUPDR);
}

unsigned int getGPIOBitSetResetRegister(gpio_device device) {
	return registerGetValue(&device->BSRR);
}

unsigned int getGPIODeviceAFRLRegister(gpio_device device) {
	return registerGetValue(&device->AFR[0]);
}

unsigned int getGPIODeviceAFRHRegister(gpio_device device) {
	return registerGetValue(&device->AFR[1]);
}

void setGPIOInputDataRegister(gpio_device device, unsigned int value) {
	device->IDR = value;
}
