/*
 * TIMER_Driver.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <stdint.h>
#include "DMA_Driver.h"

#define CONFIG_ERROR	-1
#define CONFIG_OK		1

#define FORWARD_DIR		-1
#define BACKWARD_DIR	 1

#define TDE 			1UL << 14
#define CC4DE			1UL << 12
#define CC3DE 			1UL << 11
#define CC2DE			1UL << 10
#define CC1DE			1UL << 9
#define UDE 			1UL << 8
#define TIE				1UL << 6
#define CC4IE 			1UL << 4
#define CC3IE 			1UL << 3
#define CC2IE 			1UL << 2
#define CC1IE			1UL << 1
#define UIE				1UL << 0


typedef struct TIM_TypeDef_t * timer_device;

typedef struct INPUT_CAPTURE_Config {
	uint8_t inputCaptureUnit;
	uint8_t activeInputMapping;
	uint8_t inputFilterDuration;
	uint8_t captureEdge;
	uint8_t inputPrescalerSetting;
	uint8_t interruptSetting;
	uint8_t dmaRequestSetting;
	uint8_t timeBasePeriod;
	uint32_t timerInputClockFrequency;
}INPUT_CAPTURE_Config;

enum {
	NO_TIMER_INTERRUPT=60,UPDATE_INTERRUPT_ENABLE=0
};

enum {
	DISABLE_DMA_REQUEST=0, ENABLE_DMA_REQUEST=1
};

enum {
	DISABLE_INTERRUPT=0, ENABLE_INTERRUPT=1
};

enum {
	NO_PRESCALER, ONE_HALF_PRESCALER=1, ONE_QUARTER_PRESCALER=2, ONE_EIGHTH_PRESCALER=3
};

enum {
	IC1=1, IC2=2, IC3=3, IC4=4
};

enum {
	DIRECT_MODE=0b01, INDIRECT_MODE=0b10, TRC=0b11
};

enum {
	NO_SAMPLES = 0, FOUR_SAMPLES = 0b0010, EIGHT_SAMPLES = 0b0011
};

enum {
	RISING_EDGE=0b000, FALLING_EDGE=0b001, BOTH_EDGES=0b101
};

enum {
	ENCODER_RISING_EDGE=0b000, ENCODER_FALLING_EDGE=0b001, ENCODER_BOTH_EDGES=0b101
};

enum {
	ENCODER_MODE_THREE=0b0011
};

enum {
	GPIO_OR_OPTION=0b00, LSI_OR_OPTION=0b01, LSE_OR_OPTION=0b10, RTC_WAKEUP_OR_OPTION=0b11,
};

typedef struct PWM_Output_Config {
	uint8_t timerChannelOneActiveFlag;
	uint8_t timerChannelTwoActiveFlag;
	uint8_t timerChannelThreeActiveFlag;
	uint8_t timerChannelFourActiveFlag;
	uint8_t timerChannelFiveActiveFlag;
	uint8_t timerChannelSixActiveFlag;
	uint8_t timerChannelOneNActiveFlag;
	uint8_t timerChannelTwoNActiveFlag;
	uint8_t timerChannelThreeNActiveFlag;
}PWM_Output_Config;

typedef struct Burst_Transfer_Options {
	uint8_t timerRegisterOffset;
	uint32_t bufferLength;
	uint32_t burstBufferAddress;
	uint16_t numberOfTransferRequests;
}Burst_Transfer_Options;

typedef struct PWM_TIMER_Config {
	uint8_t timerType;
	uint32_t TimerInputClockFrequency;
	uint32_t TimerTargetPWMFrequency;
	uint8_t pwmMode;
	uint8_t timerChannelOnePolarity;
	uint8_t timerChannelTwoPolarity;
	uint8_t timerChannelThreePolarity;
	uint8_t timerChannelFourPolarity;
	uint8_t timerChannelFivePolarity;
	uint8_t timerChannelSixPolarity;
	uint8_t timerChannelOneNPolarity;
	uint8_t timerChannelTwoNPolarity;
	uint8_t timerChannelThreeNPolarity;
	uint8_t timerChannelFourNPolarity;
}PWM_TIMER_Config;

enum {
	GENERAL_PURPOSE_TIMER, ADVANCED_TIMER
};

enum{
	TIMER_DEFAULT_SETTING
};

enum{
	MILLISECOND, MICROSECOND
};

enum{
	EDGE_ALIGNED_MODE = 0b0110
};

enum{
	ACTIVE_HIGH=1, ACTIVE_LOW
};

enum{
	DISABLED=1, ENABLED
};

int8_t configurePWMTimer (timer_device device, PWM_TIMER_Config * pwmTimerConfig, uint8_t channelNumber);

void configureTimeBaseGeneration (timer_device device, uint16_t timerPrescaler,	uint32_t timerARRValue);

void configureTimerDMAInterrupts(timer_device device, uint16_t interruptEnableMask);

void configureInputCapture(timer_device device, INPUT_CAPTURE_Config * inputCaptureConfig);

void configureTimerOptionRegister(timer_device device, uint8_t optionRegisterValue);

void configureEncoderMode(timer_device device);

void forceUpdateGeneration(timer_device device);

uint32_t readTimerCNTRegister(timer_device device);

uint8_t readEncoderDirection(timer_device device);

void enableTimer (timer_device device);

void disableTimer (timer_device device);

void DMA_Burst_Transfer_Setup (timer_device device, DMA_Stream_Config * dmaStreamConfig, Burst_Transfer_Options * burstOptons);

void updateTimerCCRxRegister (timer_device device, uint16_t CCRValue, uint8_t channelNumber);

void setupTimerRegisterBurstTransaction (timer_device device, Burst_Transfer_Options * burstOptons);

void setPWMOutputActivation(timer_device device, PWM_Output_Config * outputConfig);

void checkAndClearTimerUpdateInterruptFlag (timer_device device);


#endif /* TIMER_DRIVER_H_ */
