/*
 * timers_integration_test.c
 *
 *  Created on: Sep 7, 2024
 *      Author: root
 */

#include "timers_integration_test.h"
#include "TIMER_Driver.h"
#include "TIMER_Dependency_Injection.h"
#include <string.h>
#include "DMA_Driver.h"
#include "DMA_Dependency_Injection.h"
#include "GPIODriver.h"
#include "GPIO_Dependency_Injection.h"
#include "GPIO_Device_Common.h"
#include "stm32f7xx.h"
#include "register_bit_utils.h"


static timer_device timer12;
static timer_device timer4;
static timer_device timer7;
static dma_stream_device dmaStream;
static dma_device dmaDevice;
static gpio_device gpioPortB;

static uint16_t burstArray[800];

void led_pwm_burst_operation (void) {

	Burst_Transfer_Options burstOptions = {0};
	burstOptions.timerRegisterOffset = 0xE;
	burstOptions.bufferLength = 800;
	burstOptions.burstBufferAddress = (uint32_t)burstArray;
	burstOptions.numberOfTransferRequests = 1;

	setupTimerRegisterBurstTransaction (timer4, &burstOptions);

	DMA_Stream_Config  dmaStreamConfig;
	DMA_Burst_Transfer_Setup (timer4, &dmaStreamConfig, &burstOptions);

	dmaStreamConfig.priorityLevel = HIGH_PRIORITY;
	dmaStreamConfig.channelSelection = CHANNEL_TWO;
	dmaStreamConfig.fifoLevel = HALF_LEVEL_FIFO;
	dmaStreamConfig.fifoSetting = ENABLE_FIFO;
	dmaStreamConfig.circularMode = DISABLE_CIRCULAR_MODE;
	dmaStreamConfig.doubleBufferMode = DISABLE_DOUBLE_BUFFER_MODE;

	configureTimerDMAInterrupts(timer4, UDE);

	disableDMAStream(dmaStream);
	configureDMAStream(dmaStream, dmaDevice, &dmaStreamConfig);
	enableDMAStream(dmaStream);

	delay(550);
}

void led_pwm_brighted_dimming_test (void) {

	for (int i = 0; i < 800; i++) {
		updateTimerCCRxRegister (timer12, i, 1);
		updateTimerCCRxRegister (timer4, i, 2);
		delay(1);
	}
	for (int i = 800; i > 0; i--) {
		updateTimerCCRxRegister (timer12, i, 1);
		updateTimerCCRxRegister (timer4, i, 2);
		delay(1);
	}
}


void setup_timers_integration_test (void) {

	for(int index = 0; index < 800; index++) {
		burstArray[index] = index;
	}

	Initialize_TIMER4 ();
	Initialize_TIMER7 ();
	Initialize_TIMER12 ();
	Initialize_DMA1();
	initialize_GPIO_PORTB();

	timer12 = getTimerDeviceInstance(TIM_12);
	timer4 = getTimerDeviceInstance(TIM_4);
	timer7 = getTimerDeviceInstance(TIM_7);

	dmaStream = getDMAStreamInstance(DMA_STREAM_6);
	dmaDevice = getDMADeviceInstance(DMA_1);
	gpioPortB = getGPIODeviceInstance (PORTB);

	GPIOPortConfiguration gpioConfigPortB;
	memset(&gpioConfigPortB, 0, sizeof(GPIOPortConfiguration));

	gpioConfigPortB.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioConfigPortB.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioConfigPortB.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioConfigPortB.gpioPUPDConfiguration = PULL_DOWN;

	gpioConfigPortB.gpioAFRLConfiguration = AF2;
	configureGPIODevice(gpioPortB, &gpioConfigPortB, PIN7);

	gpioConfigPortB.gpioAFRHConfiguration = AF9;
	configureGPIODevice(gpioPortB, &gpioConfigPortB, PIN14);

	disableTimer(timer12);
	disableTimer(timer4);

	configureTimeBaseGeneration (timer12, 0, 799);
	configureTimeBaseGeneration (timer4, 0, 799);

	PWM_TIMER_Config pwmTimerConfig;
	memset(&pwmTimerConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_TIMER_Config));
	pwmTimerConfig.pwmMode = EDGE_ALIGNED_MODE;
	pwmTimerConfig.timerType = GENERAL_PURPOSE_TIMER;
	pwmTimerConfig.timerChannelOnePolarity = ACTIVE_HIGH;
	configurePWMTimer(timer12, &pwmTimerConfig, 1);
	pwmTimerConfig.timerChannelTwoPolarity = ACTIVE_HIGH;
	configurePWMTimer(timer4, &pwmTimerConfig, 2);

	enableTimer(timer12);
	enableTimer(timer4);


	disableTimer(timer7);

	configureTimeBaseGeneration (timer7, 15, 999);

	enableTimer(timer7);

	PWM_Output_Config outputConfigTimer12;
	memset(&outputConfigTimer12,TIMER_DEFAULT_SETTING, sizeof(PWM_Output_Config));
	outputConfigTimer12.timerChannelOneActiveFlag = ENABLED;
	setPWMOutputActivation(timer12, &outputConfigTimer12);


	PWM_Output_Config outputConfigTimer4;
	memset(&outputConfigTimer4,TIMER_DEFAULT_SETTING, sizeof(PWM_Output_Config));
	outputConfigTimer4.timerChannelTwoActiveFlag = ENABLED;
	setPWMOutputActivation(timer4, &outputConfigTimer4);

}

void delay(int ms) {
	checkAndClearTimerUpdateInterruptFlag(timer7);
	for(; ms>0 ;ms--) {
		checkAndClearTimerUpdateInterruptFlag(timer7);
	}
}


