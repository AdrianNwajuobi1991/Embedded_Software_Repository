/*
 *  Created on: Oct 4, 2024
 *      Author: root
 */

#include "timer_encoder_mode_integration_test.h"
#include "usart_integration_test.h"
#include "TIMER_Driver.h"
#include "TIMER_Dependency_Injection.h"
#include <string.h>
#include "GPIODriver.h"
#include "GPIO_Dependency_Injection.h"
#include "GPIO_Device_Common.h"
#include "gpio_integration_test.h"

static gpio_device gpioPortA;
static timer_device timer3;

static uint32_t prev_encoder_value = 0;
static uint8_t direction = 0;
static uint32_t current_encoder_value = 0;

void encoder_position_test (void) {
	current_encoder_value = readTimerCNTRegister(timer3);
	if(current_encoder_value != prev_encoder_value)
	{
		prev_encoder_value = current_encoder_value;
		turn_on_BLUE_LED_PORTB();
	}else{
		turn_off_BLUE_LED_PORTB();
	}
}

void encoder_direction_test (void) {
	direction = readEncoderDirection(timer3);
	if (direction == FORWARD_DIR) {
		turn_off_RED_LED_PORTB();
		turn_on_GREEN_LED_PORTB();
	}else{
		turn_off_GREEN_LED_PORTB();
		turn_on_RED_LED_PORTB();
	}
}

timer_device getEncoderTimer (void) {
	return timer3;
}


void setup_timer_encoder_mode_integration_test (void) {

	Initialize_TIMER3 ();
	initialize_GPIO_PORTA();

	timer3 = getTimerDeviceInstance(TIM_3);
	gpioPortA = getGPIODeviceInstance (PORTA);

	GPIOPortConfiguration gpioConfigPortA;
	memset(&gpioConfigPortA, 0, sizeof(GPIOPortConfiguration));

	gpioConfigPortA.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioConfigPortA.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioConfigPortA.gpioOutputTypeConfiguration = OPEN_DRAIN;
	gpioConfigPortA.gpioPUPDConfiguration = PULL_UP;

	gpioConfigPortA.gpioAFRLConfiguration = AF2;
	configureGPIODevice(gpioPortA, &gpioConfigPortA, PIN6); //TIM3_CH1
	configureGPIODevice(gpioPortA, &gpioConfigPortA, PIN7); //TIM3_CH2

	configureEncoderMode (timer3);
	enableTimer (timer3);
	//forceUpdateGeneration(timer3);
}
