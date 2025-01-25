/*
 * RCCDriverTests.h
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#ifndef RCCDRIVERTESTS_H_
#define RCCDRIVERTESTS_H_

void test_216_MHZ_Core_Clock_Config_Main_PLLR_PLLQ_PLLP_PLLN_PLLM (void);

void test_select_HSE_AS_Main_PLL_Clock_source (void);

void test_RCC_HSE_Clock_Source_Enable_Main_PLL_HSE_BYPASS_Enable (void);

void test_RCC_MAIN_PLL_Enable_OTHER_PLLS_DISABLE (void);

void test_RCC_AHB_APB1_APB2_Prescalers_USE_DIV_4_AHB_DIV_8_APB1_DIV_16_APB2 (void);

void test_system_Clock_Switch_To_PLL (void);

void test_RCC_RTC_HSE_Prescaler_DIV4 (void);

void test_RCC_Dedicated_Clocks_Config_Register_One_SAI2ClockSelect (void);

void test_RTC_Clock_Source_Select_AND_ENABLE_RTC (void);

void test_RCC_APB_1_USART3_LPENR_Clock_Disable_In_Low_Power_Mode (void);


#endif /* RCCDRIVERTESTS_H_ */
