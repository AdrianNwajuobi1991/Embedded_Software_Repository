/*
 * GPIO_Dependency_Injection_Container.c
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */
#include "stm32f7xx.h"
#include "GPIO_Dependency_Injection.h"
#include "STM32F767ZIGPIODeviceLayout.h"
#include "register_bit_utils.h"
#include "GPIO_Device_Common.h"

#define GPIOAEN_BITPOS  0
#define GPIOBEN_BITPOS	1
#define GPIODEN_BITPOS	3
#define GPIOCEN_BITPOS	2

gpio_device getGPIODeviceInstance (int instance) {
	if (instance == PORTA) {
		return (gpio_device)GPIOA_BASE;
	}
	if (instance == PORTB) {
		return (gpio_device)GPIOB_BASE;
	}
	if (instance == PORTC) {
		return (gpio_device)GPIOC_BASE;
	}
	if (instance == PORTD) {
		return (gpio_device)GPIOD_BASE;
	}
}

void initialize_GPIO_PORTA (void) {
	registerSetBit (&RCC->AHB1ENR, GPIOAEN_BITPOS);
}

void initialize_GPIO_PORTB (void) {
	registerSetBit (&RCC->AHB1ENR, GPIOBEN_BITPOS);
}

void initialize_GPIO_PORTC (void) {
	registerSetBit (&RCC->AHB1ENR, GPIOCEN_BITPOS);
}

void initialize_GPIO_PORTD (void) {
	registerSetBit (&RCC->AHB1ENR, GPIODEN_BITPOS);
}

void GPIODeviceCleanUp (gpio_device device, GPIOPortConfiguration* config) {

}


