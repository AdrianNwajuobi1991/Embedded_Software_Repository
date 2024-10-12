/*
 * spi_integration_test.c
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#include "USART_Dependency_Injection.h"
#include "GPIO_Dependency_Injection.h"
#include "gpio_integration_test.h"
#include "usart_integration_test.h"
#include <string.h>
#include <stdbool.h>

static usart_device usartDevice5 = 0;
static gpio_device gpioPortB = 0;

static usart_device usartDevice3 = 0;
static gpio_device gpioPortD = 0;

void setup_usart_default (void) {
	usartDevice3 = getUSARTDeviceInstance(USART_INSTANCE_3);
	gpioPortD = getGPIODeviceInstance(PORTD);
	initialize_USART3_Device();
	GPIOPortConfiguration gpioPortDConfig;

	memset(&gpioPortDConfig, 0, sizeof(gpioPortDConfig));

	gpioPortDConfig.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioPortDConfig.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioPortDConfig.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioPortDConfig.gpioPUPDConfiguration = PULL_UP;
	gpioPortDConfig.gpioAFRHConfiguration = AF7; //USART3 functions

	configureGPIODevice(gpioPortD, &gpioPortDConfig, PIN9); //RX Pin
	configureGPIODevice(gpioPortD, &gpioPortDConfig, PIN8); //TX Pin

	USART_Config usartConfig;
	usartConfig.baud_rate = 115200;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_16X;
	usartConfig.use_rx_interrupt = false;
	usartConfig.use_tx_interrupt = false;

	configureUSARTDevice (usartDevice3, &usartConfig);
	enableUSARTDevice (usartDevice3);
}

void setup_usart_alternate (void) {
	usartDevice5 = getUSARTDeviceInstance(USART_INSTANCE_5);
	gpioPortB = getGPIODeviceInstance(PORTB);
	initialize_USART5_Device();
	GPIOPortConfiguration gpioPortBConfig;

	memset(&gpioPortBConfig, 0, sizeof(gpioPortBConfig));

	gpioPortBConfig.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioPortBConfig.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioPortBConfig.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioPortBConfig.gpioPUPDConfiguration = PULL_UP;
	gpioPortBConfig.gpioAFRHConfiguration = AF7; //UART5 functions

	configureGPIODevice(gpioPortB, &gpioPortBConfig, PIN8); //RX Pin
	configureGPIODevice(gpioPortB, &gpioPortBConfig, PIN9); //TX Pin

	USART_Config usartConfig;
	usartConfig.baud_rate = 115200;
	usartConfig.clock_source_speed = 16000000;
	usartConfig.oversampling_mode = OVERSAMPLE_16X;
	usartConfig.use_rx_interrupt = false;
	usartConfig.use_tx_interrupt = false;

	configureUSARTDevice (usartDevice5, &usartConfig);
	enableUSARTDevice (usartDevice5);
}
