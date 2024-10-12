/*
 * timers_input_capture_integration_test.c
 *
 *  Created on: Oct 8, 2024
 *      Author: root
 */

#include "TIMER_Driver.h"
#include "TIMER_Dependency_Injection.h"
#include "GPIODriver.h"
#include "GPIO_Dependency_Injection.h"
#include "GPIO_Device_Common.h"
#include "gpio_integration_test.h"
#include "timer_input_capture_integration_test.h"
#include <string.h>
#include "stm32f7xx.h"


static timer_device timer5;
static timer_device timer4;
static gpio_device gpioPortA;
static gpio_device gpioPortD;

static volatile uint32_t CCR1Value = 0;

void capture_tim5_channel_1 (void) {
	if (registerTestBitPosition (&timer5->SR, 1) == BIT_SET) {
		CCR1Value = timer5->CCR1;
		toggle_all_LEDs_PORTB();
	}
}

void setup_input_capture (void) {
	/* Initialize GPIO Port A */
	initialize_GPIO_PORTA();
	gpioPortA = getGPIODeviceInstance (PORTA);

	/* Initialize GPIO Port D */
	initialize_GPIO_PORTD();
	gpioPortD = getGPIODeviceInstance (PORTD);

	GPIOPortConfiguration gpioConfig;

	/* configure GPIO for timer5 channel 4 */
	memset(&gpioConfig, 0, sizeof(GPIOPortConfiguration));
	gpioConfig.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioConfig.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioConfig.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioConfig.gpioPUPDConfiguration = NO_PULLUP_PULLDOWN;
	gpioConfig.gpioAFRLConfiguration = AF2;
	configureGPIODevice(gpioPortA, &gpioConfig, PIN3); //TIM5_CH4 -> PA3

	/* configure GPIO for timer4 channel 3 */
	memset(&gpioConfig, 0, sizeof(GPIOPortConfiguration));
	gpioConfig.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioConfig.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioConfig.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioConfig.gpioPUPDConfiguration = NO_PULLUP_PULLDOWN;
	gpioConfig.gpioAFRHConfiguration = AF2;
	configureGPIODevice(gpioPortD, &gpioConfig, PIN14); //TIM4_CH3 -> PB8

	Initialize_TIMER5 ();
	Initialize_TIMER4 ();

	timer4 = getTimerDeviceInstance(TIM_4);
	timer5 = getTimerDeviceInstance(TIM_5);

	/*disable all timers */
	disableTimer(timer5);
	disableTimer(timer4);

	/* configure timer5 for 200Khz operation. */
	configureTimeBaseGeneration (timer5, 79, 0xFFFFFFFF);

	/* configure timer4 for 1KHz operation. */
	//configureTimeBaseGeneration (timer4, 0, 799);
	configureTimeBaseGeneration (timer4, 15999, 49);

	/* configure PWM for timer4 on channel 3*/
	PWM_TIMER_Config pwmTimerConfig;
	memset(&pwmTimerConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_TIMER_Config));
	pwmTimerConfig.pwmMode = EDGE_ALIGNED_MODE;
	pwmTimerConfig.timerType = GENERAL_PURPOSE_TIMER;
	pwmTimerConfig.timerChannelThreePolarity = ACTIVE_HIGH;
	configurePWMTimer(timer4, &pwmTimerConfig, 3);
	updateTimerCCRxRegister (timer4, 25, 3);

	/* configure Input capture for timer5 on channel 4 */
	INPUT_CAPTURE_Config inputCaptureConfig;
	memset(&inputCaptureConfig,TIMER_DEFAULT_SETTING, sizeof(INPUT_CAPTURE_Config));
	inputCaptureConfig.inputCaptureUnit = IC4;
	inputCaptureConfig.activeInputMapping = DIRECT_MODE;
	inputCaptureConfig.inputFilterDuration = NO_SAMPLES;
	inputCaptureConfig.captureEdge = RISING_EDGE;
	inputCaptureConfig.inputPrescalerSetting = NO_PRESCALER;
	configureInputCapture(timer5, &inputCaptureConfig);

	/*Enable PWM Output on timer4 channel 3 */
	PWM_Output_Config outputConfigTimer4;
	memset(&outputConfigTimer4,TIMER_DEFAULT_SETTING, sizeof(PWM_Output_Config));
	outputConfigTimer4.timerChannelThreeActiveFlag = ENABLED;
	setPWMOutputActivation(timer4, &outputConfigTimer4);

	enableTimer (timer4);
	enableTimer (timer5);

	configureTimerDMAInterrupts(timer5, CC4IE);
	NVIC_SetPriorityGrouping(0);
	NVIC_SetPriority (TIM5_IRQn, 1);
	NVIC_EnableIRQ (TIM5_IRQn);
}

void TIM5_IRQHandler (void) {
	if (registerTestBitPosition (&timer5->SR, 4) == BIT_SET) {
		toggle_all_LEDs_PORTB();
		CCR1Value = timer5->CCR4;
	}
}
