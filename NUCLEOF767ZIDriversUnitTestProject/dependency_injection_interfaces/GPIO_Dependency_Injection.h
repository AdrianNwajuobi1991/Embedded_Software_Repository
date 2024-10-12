/*
 * GPIO_Dependency_Injection.h
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#ifndef GPIO_DEPENDENCY_INJECTION_H_
#define GPIO_DEPENDENCY_INJECTION_H_

#include "GPIODriver.h"
#include "GPIO_Device_Common.h"

#define MAX_GPIO_INSTANCE	5

gpio_device getGPIODeviceInstance (int instance);

void initialize_GPIO_PORTA (void);

void initialize_GPIO_PORTB (void);

void initialize_GPIO_PORTC (void);

void initialize_GPIO_PORTD (void);

void GPIODeviceCleanUp (gpio_device device, GPIOPortConfiguration* config);

int getMaxNumberOfGPIOPorts (void);

#endif /* GPIO_DEPENDENCY_INJECTION_H_ */
