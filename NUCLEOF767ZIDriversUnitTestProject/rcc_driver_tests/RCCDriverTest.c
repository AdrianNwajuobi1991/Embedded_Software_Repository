/*
 * RCCDriverTest.c
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#include "unity.h"
#include "RCC_Driver.h"
#include "RCC_DriverTestHelper.h"
#include "RCCDriverTests.h"


extern rcc_device rccDevice;

void test_216_MHZ_Core_Clock_Config_Main_PLLR_PLLQ_PLLP_PLLN_PLLM (void) {
	configureRCCMainPLLRQPNMValues(rccDevice, 2, 9, 0, 216, 4);
	TEST_ASSERT_EQUAL_HEX32(0x29003604, getRCC_PLCFGRRegisterValue(rccDevice));
}

void test_select_HSE_AS_Main_PLL_Clock_source (void) {
	configureRCCMainPLLClockSource(rccDevice, HSE_CLK_SRC);
	TEST_ASSERT_EQUAL_HEX32(0x24403010, getRCC_PLCFGRRegisterValue(rccDevice));
}

void test_RCC_HSE_Clock_Source_Enable_Main_PLL_HSE_BYPASS_Enable (void) {
	configureRCCHSEClock(rccDevice, HSE_CLK_ENABLE, HSE_BYPASS_ENABLE);
	TEST_ASSERT_EQUAL_HEX32(0x00050083, getRCC_CRRegisterValue(rccDevice));
}

void test_RCC_MAIN_PLL_Enable_OTHER_PLLS_DISABLE (void) {
	uint32_t RCCPLLSetupMask = MAIN_PLL_ON;
	configureRCCPLLSetup(rccDevice, RCCPLLSetupMask);
	TEST_ASSERT_EQUAL_HEX32(0x01000083, getRCC_CRRegisterValue(rccDevice));
}

void test_RCC_AHB_APB1_APB2_Prescalers_USE_DIV_4_AHB_DIV_8_APB1_DIV_16_APB2 (void) {
	uint32_t prescalerSetupMask = AHB_PSC_DIV4 | APB1_PSC_DIV8 | APB2_PSC_DIV16;
	configureRCC_AHB_APB_Prescalers(rccDevice, prescalerSetupMask);
	TEST_ASSERT_EQUAL_HEX32(0x0000F890, getRCC_CFGRRegisterValue(rccDevice));
}

void test_RCC_RTC_HSE_Prescaler_DIV4 (void) {
	uint32_t rtcHSEPrescalerMask = RTC_HSE_DIV4;
	configureRCC_RTC_HSEPrescaler (rccDevice, rtcHSEPrescalerMask);
	TEST_ASSERT_EQUAL_HEX32(0x00040000, getRCC_CFGRRegisterValue(rccDevice));
}

void test_RTC_Clock_Source_Select_AND_ENABLE_RTC (void) {
	uint32_t rtcBackUpDomainControlMask = RTCSEL_HSE;
	configureRCC_RTC_BackUpDomainControl (rccDevice, rtcBackUpDomainControlMask);
	TEST_ASSERT_EQUAL_HEX32(0x00008300, getRCC_BDCRRegisterValue(rccDevice));
}

void test_system_Clock_Switch_To_PLL (void) {
	uint8_t systemClockSwitchMask = PLL_SYS_CLK_SWITCH;
	configureRCC_SystemClockSwitch (rccDevice, systemClockSwitchMask);
	TEST_ASSERT_EQUAL_HEX32(0x00000002, getRCC_CFGRRegisterValue(rccDevice));
}

void test_RCC_Dedicated_Clocks_Config_Register_One_SAI2ClockSelect (void) {
	configureRCC_DedicatedClockSourceRegisterOne(rccDevice, SAI2_SEL, SAI2_SEL_MASK, SAI2_CLK_SRC_TWO);
	TEST_ASSERT_EQUAL_HEX32(0x00800000, getRCC_DCKCFGR1RegisterValue(rccDevice));
}

void test_RCC_APB_1_USART3_LPENR_Clock_Disable_In_Low_Power_Mode (void) {
	configureRCC_APB1_LowPowerModeClockSetting (rccDevice, USART3_DEVICE, APB1_LPENR_CLK_DISABLE);
	TEST_ASSERT_EQUAL_HEX32(0xFFFBEFFF, getRCC_APB1LPENRRegisterValue(rccDevice));
}
