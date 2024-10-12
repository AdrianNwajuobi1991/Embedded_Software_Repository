/*
 * STM32F767ZI_TIMER_Driver.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "TIMER_Driver.h"
#include "STM32F767ZI_TIMERDeviceDriverLayout.h"
#include "register_bit_utils.h"
#include "DMA_Driver.h"
#include "DMA_Dependency_Injection.h"
#include <string.h>

static void setPWMOutputMode (timer_device device, PWM_TIMER_Config * pwmTimerConfig, uint8_t channelNumber);
static void setCCMR1OCMValues(timer_device device, PWM_TIMER_Config * pwmTimerConfig, int outputCompareNumber);
static void setCCMR2OCMValues(timer_device device, PWM_TIMER_Config * pwmTimerConfig, int outputCompareNumber);
static void setCCMR3OCMValues(timer_device device, PWM_TIMER_Config * pwmTimerConfig, int outputCompareNumber);
static void setCCERPolarityForNonInvertedOutputChannels(timer_device device, PWM_TIMER_Config * pwmTimerConfig);
static void setCCERPolarityForInvertedOutputChannels(timer_device device, PWM_TIMER_Config * pwmTimerConfig);
static void setCCERNonInvertedOutputActivationSettings(timer_device device, PWM_Output_Config * outputConfig);
static void setCCERInvertedOutputActivationSettings(timer_device device, PWM_Output_Config * outputConfig);


#define ARPE_BITPOS		7
#define UG_BITPOS		0
#define CEN_BITPOS		0
#define UIF_BITPOS		0


void configureTimeBaseGeneration (timer_device device, uint16_t timerPrescaler,	uint32_t timerARRValue) {

	registerOverwriteValue (&device->PSC, timerPrescaler);
	registerOverwriteValue (&device->ARR, timerARRValue);
}

void configureTimerDMAInterrupts(timer_device device, uint16_t interruptEnableMask) {
	device->DIER |= interruptEnableMask;
	device->SR &= ~(interruptEnableMask);
}

int8_t configurePWMTimer(timer_device device, PWM_TIMER_Config * pwmTimerConfig, uint8_t channelNumber) {
	int8_t status = CONFIG_OK;
	if (pwmTimerConfig->timerType == GENERAL_PURPOSE_TIMER || pwmTimerConfig->timerType == ADVANCED_TIMER) {
		device->CNT = 0;
		setPWMOutputMode (device, pwmTimerConfig, channelNumber);
		setCCERPolarityForNonInvertedOutputChannels(device, pwmTimerConfig);
		setCCERPolarityForInvertedOutputChannels(device, pwmTimerConfig);
	}
	if (status != CONFIG_ERROR) {
		if (pwmTimerConfig->timerType == ADVANCED_TIMER) {

		}
	}
	return status;
}

void configureTimerOptionRegister(timer_device device, uint8_t optionRegisterValue) {
	registerSetValueInBitPosition (&device->OR, optionRegisterValue, 6);
}

void configureEncoderMode(timer_device device) {
	registerSetValueInBitPosition (&device->CCMR1, DIRECT_MODE, 0);
	registerSetValueInBitPosition (&device->CCMR1, DIRECT_MODE, 8);
	registerSetValueInBitPosition (&device->CCER, ENCODER_RISING_EDGE, 1);
	registerSetValueInBitPosition (&device->CCER, ENCODER_RISING_EDGE, 5);
	registerSetValueInBitPosition (&device->SMCR, ENCODER_MODE_THREE, 0);
}

void forceUpdateGeneration(timer_device device) {
	device->CNT = 0;
	registerSetBit (&device->EGR, 0);
}

uint32_t readTimerCNTRegister(timer_device device) {
	return device->CNT;
}

uint8_t readEncoderDirection(timer_device device) {
	if (registerTestBitPosition (&device->CR1, 4) == BIT_SET) {
		return FORWARD_DIR;
	}
	return BACKWARD_DIR;
}

void configureInputCapture(timer_device device, INPUT_CAPTURE_Config * inputCaptureConfig) {

	if (inputCaptureConfig->inputCaptureUnit == IC1 ) {
		registerSetValueInBitPosition (&device->CCMR1, inputCaptureConfig->activeInputMapping, 0);
	}

	if (inputCaptureConfig->inputCaptureUnit == IC2) {
		registerSetValueInBitPosition (&device->CCMR1, inputCaptureConfig->activeInputMapping, 8);
	}

	if (inputCaptureConfig->inputCaptureUnit == IC3) {
		registerSetValueInBitPosition (&device->CCMR2, inputCaptureConfig->activeInputMapping, 0);
	}

	if (inputCaptureConfig->inputCaptureUnit == IC4) {
		registerSetValueInBitPosition (&device->CCMR2, inputCaptureConfig->activeInputMapping, 8);
	}

	if (inputCaptureConfig->inputCaptureUnit == IC1) {
		registerSetValueInBitPosition (&device->CCMR1, inputCaptureConfig->inputFilterDuration, 4);
		registerSetValueInBitPosition (&device->CCMR1, inputCaptureConfig->inputPrescalerSetting, 2);
		registerSetValueInBitPosition (&device->CCER, inputCaptureConfig->captureEdge, 1);
		registerSetBit (&device->CCER, 0);
	}
	if (inputCaptureConfig->inputCaptureUnit == IC4) {
		registerSetValueInBitPosition (&device->CCMR2, inputCaptureConfig->inputFilterDuration, 12);
		registerSetValueInBitPosition (&device->CCMR2, inputCaptureConfig->inputPrescalerSetting, 10);
		registerSetValueInBitPosition (&device->CCER, inputCaptureConfig->captureEdge, 13);
		registerSetBit (&device->CCER, 12);
	}
}

void enableTimer(timer_device device) {
	registerSetBit(&device->CR1, CEN_BITPOS);
}

void disableTimer(timer_device device) {
	registerClearBit(&device->CR1, CEN_BITPOS);
}

void DMA_Burst_Transfer_Setup (timer_device device, DMA_Stream_Config * dmaStreamConfig, Burst_Transfer_Options * burstOptions) {
	memset(dmaStreamConfig, DMA_DEFAULT_SETTING, sizeof(DMA_Stream_Config));
	dmaStreamConfig->transferDirection = MEM_TO_PERIPH;
	dmaStreamConfig->numberOfDataItems = burstOptions->bufferLength;
	dmaStreamConfig->sourceAddress = burstOptions->burstBufferAddress;
	dmaStreamConfig->destinationAddress = (uint32_t)&device->DMAR;
	dmaStreamConfig->dataItemSize = HALF_WORD;
	dmaStreamConfig->memoryBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig->peripheralBurstSize = SINGLE_TRANSFER;
	dmaStreamConfig->memoryIncrementMode = INCREMENT;
	dmaStreamConfig->peripheralIncrementMode = FIXED;
}

void updateTimerCCRxRegister (timer_device device, uint16_t CCRValue, uint8_t channelNumber) {
	volatile uint32_t * CCRxOneToFourPtr = (volatile uint32_t *)&device->CCR1;
	volatile uint32_t * CCRxFiveToSixPtr = (volatile uint32_t *)&device->CCR5;
	if (channelNumber >= 1 && channelNumber <= 5) {
		CCRxOneToFourPtr[channelNumber-1] = CCRValue;
	}
	if (channelNumber >= 5 && channelNumber <= 6) {
		CCRxFiveToSixPtr[channelNumber-5] = CCRValue;
	}
}

void setupTimerRegisterBurstTransaction (timer_device device, Burst_Transfer_Options * burstOptions) {
	registerSetBit(&device->CR2, 3);
	registerSetValueInBitPosition(&device->DCR, burstOptions->timerRegisterOffset, 0);
	registerSetValueInBitPosition(&device->DCR, burstOptions->numberOfTransferRequests-1, 8);
}

void checkAndClearTimerUpdateInterruptFlag (timer_device device) {
	while (registerTestBitPosition (&device->SR, UIF_BITPOS) == BIT_CLEAR) {}
	registerClearBit(&device->SR, UIF_BITPOS); //reset UIF
}

void setPWMOutputActivation(timer_device device, PWM_Output_Config * outputConfig) {
	setCCERInvertedOutputActivationSettings(device, outputConfig);
	setCCERNonInvertedOutputActivationSettings(device, outputConfig);
}

#define CC1NE_BITPOS	2
#define CC2NE_BITPOS	6
#define CC3NE_BITPOS	10

static void setCCERInvertedOutputActivationSettings(timer_device device, PWM_Output_Config * outputConfig) {
	if (outputConfig->timerChannelOneNActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC1NE_BITPOS);
	}
	if (outputConfig->timerChannelOneNActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC1NE_BITPOS);
	}

	if (outputConfig->timerChannelTwoNActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC2NE_BITPOS);
	}
	if (outputConfig->timerChannelTwoNActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC2NE_BITPOS);
	}

	if (outputConfig->timerChannelThreeNActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC3NE_BITPOS);
	}
	if (outputConfig->timerChannelThreeNActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC3NE_BITPOS);
	}
}

#define CC1E_BITPOS		0
#define CC2E_BITPOS		4
#define CC3E_BITPOS		8
#define CC4E_BITPOS		12
#define CC5E_BITPOS		16
#define CC6E_BITPOS		20

static void setCCERNonInvertedOutputActivationSettings(timer_device device, PWM_Output_Config * outputConfig) {

	if (outputConfig->timerChannelOneActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC1E_BITPOS);
	}
	if (outputConfig->timerChannelOneActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC1E_BITPOS);
	}

	if (outputConfig->timerChannelTwoActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC2E_BITPOS);
	}
	if (outputConfig->timerChannelTwoActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC2E_BITPOS);
	}

	if (outputConfig->timerChannelThreeActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC3E_BITPOS);
	}
	if (outputConfig->timerChannelThreeActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC3E_BITPOS);
	}

	if (outputConfig->timerChannelFourActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC4E_BITPOS);
	}
	if (outputConfig->timerChannelFourActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC4E_BITPOS);
	}

	if (outputConfig->timerChannelFiveActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC5E_BITPOS);
	}
	if (outputConfig->timerChannelFiveActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC5E_BITPOS);
	}

	if (outputConfig->timerChannelSixActiveFlag == DISABLED) {
		registerSetValueInBitPosition(&device->CCER, 0, CC6E_BITPOS);
	}
	if (outputConfig->timerChannelSixActiveFlag == ENABLED) {
		registerSetValueInBitPosition(&device->CCER, 1, CC6E_BITPOS);
	}

}

#define CC1NP_BITPOS	3
#define CC2NP_BITPOS	7
#define CC3NP_BITPOS	11
#define CC4NP_BITPOS	15

static void setCCERPolarityForInvertedOutputChannels(timer_device device, PWM_TIMER_Config * pwmTimerConfig) {
	if (pwmTimerConfig->timerChannelOneNPolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelOneNPolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC1NP_BITPOS);
		}
		if (pwmTimerConfig->timerChannelOneNPolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC1NP_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelTwoNPolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelTwoNPolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC2NP_BITPOS);
		}
		if (pwmTimerConfig->timerChannelTwoNPolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC2NP_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelThreeNPolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelThreeNPolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC3NP_BITPOS);
		}
		if (pwmTimerConfig->timerChannelThreeNPolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC3NP_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelFourNPolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelFourNPolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC4NP_BITPOS);
		}
		if (pwmTimerConfig->timerChannelFourNPolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC4NP_BITPOS);
		}
	}
}

#define CC1P_BITPOS		1
#define CC2P_BITPOS		5
#define CC3P_BITPOS		9
#define CC4P_BITPOS		13
#define CC5P_BITPOS		17
#define CC6P_BITPOS		21

static void setCCERPolarityForNonInvertedOutputChannels(timer_device device, PWM_TIMER_Config * pwmTimerConfig) {
	if (pwmTimerConfig->timerChannelOnePolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelOnePolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC1P_BITPOS);
		}
		if (pwmTimerConfig->timerChannelOnePolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC1P_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelTwoPolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelTwoPolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC2P_BITPOS);
		}
		if (pwmTimerConfig->timerChannelTwoPolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC2P_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelThreePolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelThreePolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC3P_BITPOS);
		}
		if (pwmTimerConfig->timerChannelThreePolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC3P_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelFourPolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelFourPolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC4P_BITPOS);
		}
		if (pwmTimerConfig->timerChannelFourPolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC4P_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelFivePolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelFivePolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC5P_BITPOS);
		}
		if (pwmTimerConfig->timerChannelFivePolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC5P_BITPOS);
		}
	}
	if (pwmTimerConfig->timerChannelSixPolarity != TIMER_DEFAULT_SETTING) {
		if (pwmTimerConfig->timerChannelSixPolarity == ACTIVE_HIGH) {
			registerSetValueInBitPosition(&device->CCER, 0, CC6P_BITPOS);
		}
		if (pwmTimerConfig->timerChannelSixPolarity == ACTIVE_LOW) {
			registerSetValueInBitPosition(&device->CCER, 1, CC6P_BITPOS);
		}
	}
}

static void setPWMOutputMode (timer_device device, PWM_TIMER_Config * pwmTimerConfig, uint8_t channelNumber) {
	if (channelNumber == 1 ||channelNumber == 2) {
		setCCMR1OCMValues(device, pwmTimerConfig, channelNumber);
	}
	if (channelNumber == 3 ||channelNumber == 4) {
		setCCMR2OCMValues(device, pwmTimerConfig, channelNumber);
	}
	if (channelNumber == 5 ||channelNumber == 6) {
		setCCMR3OCMValues(device, pwmTimerConfig, channelNumber);
	}
}

#define OC1M_3_BITPOS	16
#define OC1M_2_0_BITPOS	4
#define OC2M_3_BITPOS	24
#define OC2M_2_0_BITPOS	12
#define OC3M_3_BITPOS	16
#define OC3M_2_0_BITPOS	4
#define OC4M_3_BITPOS	24
#define OC4M_2_0_BITPOS	12
#define OC5M_3_BITPOS	16
#define OC5M_2_0_BITPOS	4
#define OC6M_3_BITPOS	24
#define OC6M_2_0_BITPOS	12

static void setCCMR1OCMValues(timer_device device, PWM_TIMER_Config * pwmTimerConfig, int outputCompareNumber) {
	if (outputCompareNumber == 1) {
		registerSetValueInBitPosition(&device->CCMR1, (pwmTimerConfig->pwmMode & (1 << 3))>>3, OC1M_3_BITPOS);//OC1M[3] bit
		registerSetValueInBitPosition(&device->CCMR1, (pwmTimerConfig->pwmMode & 0x7) , OC1M_2_0_BITPOS); //OC1M[2:0]
	}
	if (outputCompareNumber == 2) {
		registerSetValueInBitPosition(&device->CCMR1, (pwmTimerConfig->pwmMode & (1 << 3))>>3, OC2M_3_BITPOS);//OC2M[3] bit
		registerSetValueInBitPosition(&device->CCMR1, (pwmTimerConfig->pwmMode & 0x7), OC2M_2_0_BITPOS); //OC2M[2:0]
	}
}

static void setCCMR2OCMValues(timer_device device, PWM_TIMER_Config * pwmTimerConfig, int outputCompareNumber) {
	if (outputCompareNumber == 3) {
		registerSetValueInBitPosition(&device->CCMR2, (pwmTimerConfig->pwmMode & (1 << 3))>>3, OC3M_3_BITPOS);//OC3M[3] bit
		registerSetValueInBitPosition(&device->CCMR2, (pwmTimerConfig->pwmMode & 0x7), OC3M_2_0_BITPOS); //OC3M[2:0]
	}
	if (outputCompareNumber == 4) {
		registerSetValueInBitPosition(&device->CCMR2, (pwmTimerConfig->pwmMode & (1 << 3))>>3, OC4M_3_BITPOS);//OC4M[3] bit
		registerSetValueInBitPosition(&device->CCMR2, (pwmTimerConfig->pwmMode & 0x7), OC4M_2_0_BITPOS); //OC4M[2:0]
	}
}
static void setCCMR3OCMValues(timer_device device, PWM_TIMER_Config * pwmTimerConfig, int outputCompareNumber) {
	if (outputCompareNumber == 5) {
		registerSetValueInBitPosition(&device->CCMR3, (pwmTimerConfig->pwmMode & (1 << 3))>>3, OC5M_3_BITPOS);//OC5M[3] bit
		registerSetValueInBitPosition(&device->CCMR3, (pwmTimerConfig->pwmMode & 0x7), OC5M_2_0_BITPOS); //OC5M[2:0]
	}
	if (outputCompareNumber == 6) {
		registerSetValueInBitPosition(&device->CCMR3, (pwmTimerConfig->pwmMode & (1 << 3))>>3, OC6M_3_BITPOS);//OC6M[3] bit
		registerSetValueInBitPosition(&device->CCMR3, (pwmTimerConfig->pwmMode & 0x7), OC6M_2_0_BITPOS); //OC6M[2:0]
	}
}

