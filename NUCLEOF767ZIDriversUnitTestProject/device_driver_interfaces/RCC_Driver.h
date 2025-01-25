/*
 * RCC_Driver.h
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#ifndef RCC_DRIVER_H_
#define RCC_DRIVER_H_

#include <stdint.h>

#define MAIN_PLL_ON			1UL << 24
#define I2S_PLL_ON			1UL << 26
#define SAI_PLL_ON			1UL << 28
//#define AHB_PSC_DIV4		9UL << 4
//#define APB1_PSC_DIV8		6UL << 10
//#define APB2_PSC_DIV16		7UL << 13
//#define APB2_PSC_DIV4		5UL << 13
#define PLL_SYS_CLK_SWITCH	2UL << 0
#define HSE_SYS_CLK_SWITCH	1UL << 0


enum {
	HSI_CLK_SRC = 0, HSE_CLK_SRC = 1,
};

enum {
	RTC_HSE_DIV4 = 0b00100 << 16,
	AHB_PSC_DIV4 = 9UL << 4,
	APB1_PSC_DIV8 = 6UL << 10,
	APB2_PSC_DIV16 = 7UL << 13,
	APB2_PSC_DIV4 = 5UL << 13
};

enum {
	RTCSEL_HSE = 0b11 << 8 | 1 << 15
};

enum {
	HSE_CLK_DISABLE = 0, HSE_CLK_ENABLE = 1
};

enum {
	HSE_BYPASS_DISABLE = 0, HSE_BYPASS_ENABLE = 1
};

enum {
	SAI2_SEL=22
};

enum {
	SAI2_CLK_SRC_TWO = 0b10
};

enum {
	SAI2_SEL_MASK = 0b11
};

enum {
	USART3_DEVICE=18, GPIOB_DEVICE=1
};

enum {
	APB1_LPENR_CLK_DISABLE=0, APB1_LPENR_CLK_ENABLE=1
};

typedef struct RCC_TypeDef_t * rcc_device;

void configureRCCMainPLLRQPNMValues(rcc_device device, uint16_t PLLR, uint16_t PLLQ, uint16_t PLLP, uint16_t PLLN, uint16_t PLLM);

void configureRCCMainPLLClockSource (rcc_device device, uint8_t pllSRCValue);

void configureRCCHSEClock(rcc_device device, uint8_t hseValue, uint8_t hseByPassValue);

void configureRCCPLLSetup(rcc_device device, uint32_t pllSetupMask);

void configureRCC_AHB_APB_Prescalers(rcc_device device, uint32_t prescalerSetupMask);

void configureRCC_RTC_BackUpDomainControl (rcc_device device, uint32_t rtcClockSelectFlag);

void configureRCC_RTC_HSEPrescaler (rcc_device device, uint32_t rtcHSEPrescalerMask);

void configureRCC_SystemClockSwitch (rcc_device device, uint8_t systemClockSwitchMask);

void configureRCC_APB1_LowPowerModeClockSetting (rcc_device device, uint8_t apb1Device, uint8_t clockSettingFlag);

void configureRCC_APB2_LowPowerModeClockSetting (rcc_device device, uint8_t apb2Device, uint8_t clockSettingFlag);

void configureRCC_AHB1_LowPowerModeClockSetting (rcc_device device, uint8_t ahb1Device, uint8_t clockSettingFlag);

void configureRCC_AHB2_LowPowerModeClockSetting (rcc_device device, uint8_t ahb2Device, uint8_t clockSettingFlag);

void configureRCC_AHB3_LowPowerModeClockSetting (rcc_device device, uint8_t ahb3Device, uint8_t clockSettingFlag);

void configureRCC_DedicatedClockSourceRegisterOne(rcc_device device, uint8_t deviceNumber,
		uint16_t deviceNumberMask, uint8_t deviceClockSource);

void configureRCC_DedicatedClockSourceRegisterTwo(rcc_device device, uint8_t deviceNumber,
		uint16_t deviceNumberMask, uint8_t deviceClockSource);

#endif /* RCC_DRIVER_H_ */
