/*
 * TIMERDriverTest.c
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#include "unity.h"
#include "TIMERDriverTest.h"
#include "TIMERDriverTestHelper.h"
#include "TIMER_Driver.h"
#include <string.h>
#include <stdint.h>

extern timer_device timerDevice;


void test_TIMER_Default_Register_Values (void) {
	TEST_ASSERT_EQUAL_HEX32(0x0000FFFF, getTimerARRValue(timerDevice));
}

void test_TIME_BASE_UNIT_200MS_32_BIT_TIMER_FCK_CNT_1MHZ_TIM_RCC_CLK_16MHZ (void) {
	configureTimeBaseGeneration (timerDevice, 15, 199999);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerCR1Value(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x0000000F, getTimerPSCValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00030D3F, getTimerARRValue(timerDevice));
}

void test_Timer_OR_Register_Choose_LSE_Oscillator_Option (void) {
	configureTimerOptionRegister(timerDevice, LSE_OR_OPTION);
	TEST_ASSERT_EQUAL_HEX32(0x00000080, getTimerORValue(timerDevice));
}

void test_Encoder_Mode_Setup (void) {
	configureEncoderMode(timerDevice);
	TEST_ASSERT_EQUAL_HEX32(0x00000101, getTimerCCMR1Value(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000003, getTimerSMCRValue(timerDevice));
}

void test_TIMER_INTERRUPTS_Config_DIER_REGISTER_ALL_INTERRUPTS_ENABLED (void) {
	uint32_t interruptEnableMask = TDE | CC4DE | CC3DE | CC2DE | CC1DE | UDE | TIE | CC4IE | CC3IE | CC2IE | CC1IE | UIE;
	configureTimerDMAInterrupts(timerDevice, interruptEnableMask);
	TEST_ASSERT_EQUAL_HEX32(0x00005F5F, getTimerDIERValue(timerDevice));
}

void test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI1_8_Samples_NO_INTERRUPTS (void) {
	INPUT_CAPTURE_Config inputCaptureConfig;
	memset(&inputCaptureConfig,TIMER_DEFAULT_SETTING, sizeof(INPUT_CAPTURE_Config));
	inputCaptureConfig.inputCaptureUnit = IC1;
	inputCaptureConfig.activeInputMapping = DIRECT_MODE;
	inputCaptureConfig.inputFilterDuration = EIGHT_SAMPLES;
	inputCaptureConfig.captureEdge = RISING_EDGE;
	inputCaptureConfig.inputPrescalerSetting = NO_PRESCALER;
	configureInputCapture(timerDevice, &inputCaptureConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00000001, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000031, getTimerCCMR1Value(timerDevice));
	//TEST_ASSERT_EQUAL_INT32(CONFIG_OK, status);
}

void test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI1_NO_Samples_NO_PRESCALER_Allow_INTERRUPTS_NO_DMA (void) {
	INPUT_CAPTURE_Config inputCaptureConfig;
	memset(&inputCaptureConfig,TIMER_DEFAULT_SETTING, sizeof(INPUT_CAPTURE_Config));
	inputCaptureConfig.inputCaptureUnit = IC1;
	inputCaptureConfig.activeInputMapping = DIRECT_MODE;
	inputCaptureConfig.inputFilterDuration = NO_SAMPLES;
	inputCaptureConfig.captureEdge = RISING_EDGE;
	inputCaptureConfig.inputPrescalerSetting = NO_PRESCALER;
	configureInputCapture(timerDevice, &inputCaptureConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00000001, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000001, getTimerCCMR1Value(timerDevice));
	//TEST_ASSERT_EQUAL_INT32(CONFIG_OK, status);
}

void test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI4_NO_Samples_NO_PRESCALER_Allow_INTERRUPTS_NO_DMA (void) {
	INPUT_CAPTURE_Config inputCaptureConfig;
	memset(&inputCaptureConfig,TIMER_DEFAULT_SETTING, sizeof(INPUT_CAPTURE_Config));
	inputCaptureConfig.inputCaptureUnit = IC4;
	inputCaptureConfig.activeInputMapping = DIRECT_MODE;
	inputCaptureConfig.inputFilterDuration = NO_SAMPLES;
	inputCaptureConfig.captureEdge = RISING_EDGE;
	inputCaptureConfig.inputPrescalerSetting = NO_PRESCALER;
	configureInputCapture(timerDevice, &inputCaptureConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00001000, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000100, getTimerCCMR2Value(timerDevice));
	//TEST_ASSERT_EQUAL_INT32(CONFIG_OK, status);
}

void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_NON_INVERTING_BOTH_ACTIVE_LOW (void) {

	configureTimeBaseGeneration (timerDevice, 0, 799);

	PWM_TIMER_Config pwmTimerConfig;
	memset(&pwmTimerConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_TIMER_Config));
	pwmTimerConfig.timerType = GENERAL_PURPOSE_TIMER;
	pwmTimerConfig.pwmMode = EDGE_ALIGNED_MODE;
	pwmTimerConfig.timerChannelOnePolarity = ACTIVE_LOW;
	pwmTimerConfig.timerChannelTwoPolarity = ACTIVE_LOW;
	int8_t status = configurePWMTimer(timerDevice, &pwmTimerConfig, 1);
	configurePWMTimer(timerDevice, &pwmTimerConfig, 2);
	TEST_ASSERT_EQUAL_HEX32(0x00000022, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00006060, getTimerCCMR1Value(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x0000031F, getTimerARRValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerPSCValue(timerDevice));
	TEST_ASSERT_EQUAL_INT32(CONFIG_OK, status);
}

void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_NON_INVERTING_BOTH_ACTIVE_HIGH (void) {

	configureTimeBaseGeneration (timerDevice, 0, 799);

	PWM_TIMER_Config pwmTimerConfig;
	memset(&pwmTimerConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_TIMER_Config));
	pwmTimerConfig.timerType = GENERAL_PURPOSE_TIMER;
	pwmTimerConfig.pwmMode = EDGE_ALIGNED_MODE;
	pwmTimerConfig.timerChannelOnePolarity = ACTIVE_HIGH;
	pwmTimerConfig.timerChannelTwoPolarity = ACTIVE_HIGH;
	int8_t status = configurePWMTimer(timerDevice, &pwmTimerConfig, 1);
	configurePWMTimer(timerDevice, &pwmTimerConfig, 2);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00006060, getTimerCCMR1Value(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x0000031F, getTimerARRValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerPSCValue(timerDevice));
	TEST_ASSERT_EQUAL_INT32(CONFIG_OK, status);
}

void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_INVERTING_BOTH_ACTIVE_LOW (void) {

	configureTimeBaseGeneration (timerDevice, 0, 799);

	PWM_TIMER_Config pwmTimerConfig;
	memset(&pwmTimerConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_TIMER_Config));
	pwmTimerConfig.timerType = GENERAL_PURPOSE_TIMER;
	pwmTimerConfig.pwmMode = EDGE_ALIGNED_MODE;
	pwmTimerConfig.timerChannelOneNPolarity = ACTIVE_LOW;
	pwmTimerConfig.timerChannelTwoNPolarity = ACTIVE_LOW;
	int8_t status = configurePWMTimer(timerDevice, &pwmTimerConfig, 1);
	configurePWMTimer(timerDevice, &pwmTimerConfig, 2);
	TEST_ASSERT_EQUAL_HEX32(0x00000088, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00006060, getTimerCCMR1Value(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x0000031F, getTimerARRValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerPSCValue(timerDevice));
	TEST_ASSERT_EQUAL_INT32(CONFIG_OK, status);
}

void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_INVERTING_BOTH_ACTIVE_HIGH (void) {

	configureTimeBaseGeneration (timerDevice, 0, 799);

	PWM_TIMER_Config pwmTimerConfig;
	memset(&pwmTimerConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_TIMER_Config));
	pwmTimerConfig.timerType = GENERAL_PURPOSE_TIMER;
	pwmTimerConfig.pwmMode = EDGE_ALIGNED_MODE;
	pwmTimerConfig.timerChannelOneNPolarity = ACTIVE_HIGH;
	pwmTimerConfig.timerChannelTwoNPolarity = ACTIVE_HIGH;
	int8_t status = configurePWMTimer(timerDevice, &pwmTimerConfig, 1);
	configurePWMTimer(timerDevice, &pwmTimerConfig, 2);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerCCERValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00006060, getTimerCCMR1Value(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x0000031F, getTimerARRValue(timerDevice));
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerPSCValue(timerDevice));
	TEST_ASSERT_EQUAL_INT32(CONFIG_OK, status);
}

void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_NON_INVERTED_BOTH_ENABLED (void) {
	PWM_Output_Config outputConfig;
	memset(&outputConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_Output_Config));
	outputConfig.timerChannelOneActiveFlag = ENABLED;
	outputConfig.timerChannelTwoActiveFlag = ENABLED;
	setPWMOutputActivation(timerDevice, &outputConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00000011, getTimerCCERValue(timerDevice));
}


void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_NON_INVERTED_BOTH_DISABLED (void) {
	PWM_Output_Config outputConfig;
	memset(&outputConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_Output_Config));
	outputConfig.timerChannelOneActiveFlag = DISABLED;
	outputConfig.timerChannelTwoActiveFlag = DISABLED;
	setPWMOutputActivation(timerDevice, &outputConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerCCERValue(timerDevice));
}

void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_INVERTED_BOTH_ENABLED (void) {
	PWM_Output_Config outputConfig;
	memset(&outputConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_Output_Config));
	outputConfig.timerChannelOneNActiveFlag = ENABLED;
	outputConfig.timerChannelTwoNActiveFlag = ENABLED;
	setPWMOutputActivation(timerDevice, &outputConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00000044, getTimerCCERValue(timerDevice));
}

void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_INVERTED_BOTH_DISABLED (void) {
	PWM_Output_Config outputConfig;
	memset(&outputConfig,TIMER_DEFAULT_SETTING, sizeof(PWM_Output_Config));
	outputConfig.timerChannelOneNActiveFlag = DISABLED;
	outputConfig.timerChannelTwoNActiveFlag = DISABLED;
	setPWMOutputActivation(timerDevice, &outputConfig);
	TEST_ASSERT_EQUAL_HEX32(0x00000000, getTimerCCERValue(timerDevice));
}
