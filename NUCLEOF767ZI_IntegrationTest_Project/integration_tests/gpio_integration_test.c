/*
 * gpio_integration_test.c
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#include "GPIO_Dependency_Injection.h"
#include <string.h>

static gpio_device gpioPortB;

void toggle_all_LEDs_PORTB (void) {
	uint16_t portValue = (1 << PIN0)|(1 << PIN7)|(1 << PIN14);
	toggleGPIOPortValue (gpioPortB, portValue);
}

void turn_on_all_LEDs_PORTB (void) {
	setGPIOPinNumberBSRR(gpioPortB, PIN0);
	setGPIOPinNumberBSRR(gpioPortB, PIN7);
	setGPIOPinNumberBSRR(gpioPortB, PIN14);
}

void turn_off_all_LEDs_PORTB (void) {
	resetGPIOPinNumberBSRR(gpioPortB, PIN0);
	resetGPIOPinNumberBSRR(gpioPortB, PIN7);
	resetGPIOPinNumberBSRR(gpioPortB, PIN14);
}

void turn_on_RED_LED_PORTB (void) {
	setGPIOPinNumberBSRR(gpioPortB, PIN14);
}

void turn_off_RED_LED_PORTB (void) {
	resetGPIOPinNumberBSRR(gpioPortB, PIN14);
}

void turn_on_BLUE_LED_PORTB (void) {
	setGPIOPinNumberBSRR(gpioPortB, PIN7);
}

void turn_off_BLUE_LED_PORTB (void) {
	resetGPIOPinNumberBSRR(gpioPortB, PIN7);
}

void turn_on_GREEN_LED_PORTB (void) {
	setGPIOPinNumberBSRR(gpioPortB, PIN0);
}

void turn_off_GREEN_LED_PORTB (void) {
	resetGPIOPinNumberBSRR(gpioPortB, PIN0);
}

void setup_gpio_integration_test_gpio_portB (void) {
	initialize_GPIO_PORTB();
	gpioPortB = getGPIODeviceInstance (PORTB);
	GPIOPortConfiguration gpioConfigPortB;

	memset(&gpioConfigPortB, 0, sizeof(gpioConfigPortB));

	gpioConfigPortB.gpioModeConfiguration = GENERAL_PURPOSE_OUTPUT;
	gpioConfigPortB.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioConfigPortB.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioConfigPortB.gpioPUPDConfiguration = PULL_DOWN;
	gpioConfigPortB.gpioAFRLConfiguration = AF0;

	configureGPIODevice(gpioPortB, &gpioConfigPortB, PIN0);
	configureGPIODevice(gpioPortB, &gpioConfigPortB, PIN7);

	gpioConfigPortB.gpioAFRHConfiguration = AF0;
	configureGPIODevice(gpioPortB, &gpioConfigPortB, PIN14);
}
