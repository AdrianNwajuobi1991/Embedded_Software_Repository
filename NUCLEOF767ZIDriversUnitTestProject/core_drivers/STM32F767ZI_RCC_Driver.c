/*
 * STM32F767ZI_RCC_Driver.c
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#include "STM32F767ZI_RCCDeviceDriverLayout.h"
#include "RCC_Driver.h"
#include <stdint.h>
#include "register_bit_utils.h"
#include "RCC_Dependency_Injection.h"

void configureRCCMainPLLRQPNMValues(rcc_device device, uint16_t PLLR, uint16_t PLLQ, uint16_t PLLP, uint16_t PLLN, uint16_t PLLM) {
	//clear
	registerClearValueInBitPosition (&device->PLLCFGR, 0xFFFF, 28);
	registerClearValueInBitPosition (&device->PLLCFGR, 0xFFFF, 24);
	registerClearValueInBitPosition (&device->PLLCFGR, 0xFFFF, 16);
	registerClearValueInBitPosition (&device->PLLCFGR, 0x1FF, 6);
	registerClearValueInBitPosition (&device->PLLCFGR, 0x3F, 0);
	//set
	registerSetValueInBitPosition (&device->PLLCFGR, PLLR, 28);
	registerSetValueInBitPosition (&device->PLLCFGR, PLLQ, 24);
	registerSetValueInBitPosition (&device->PLLCFGR, PLLP, 16);
	registerSetValueInBitPosition (&device->PLLCFGR, PLLN, 6);
	registerSetValueInBitPosition (&device->PLLCFGR, PLLM, 0);
}


void configureRCCMainPLLClockSource (rcc_device device, uint8_t pllSRCValue) {
	registerClearValueInBitPosition (&device->PLLCFGR, 0x1, 22);
	registerSetValueInBitPosition (&device->PLLCFGR, pllSRCValue, 22);
}


void configureRCCHSEClock(rcc_device device, uint8_t hseValue, uint8_t hseByPassValue) {
	//clear mask
	registerClearValueInBitPosition (&device->CR, 0x3, 16);
	registerSetValueInBitPosition (&device->CR, hseByPassValue, 18);
	registerSetValueInBitPosition (&device->CR, hseValue, 16);
	if (registerTestBitPosition (&device->CR, 16) == BIT_SET) {
		waitForHSEClockRDY(device);
	}
}


void configureRCCPLLSetup(rcc_device device, uint32_t pllSetupMask) {
	//clear mask
	registerClearValueInBitPosition (&device->CR, 0x3F, 24);
	device->CR |= pllSetupMask;
	if (registerTestBitPosition (&device->CR, 24) == BIT_SET) {
		waitForMainPLLRDY(device);
	}
	if (registerTestBitPosition (&device->CR, 26) == BIT_SET) {
		waitForI2SPLLRDY(device);
	}
	if (registerTestBitPosition (&device->CR, 28) == BIT_SET) {
		waitForSAIPLLRDY(device);
	}
}

void configureRCC_AHB_APB_Prescalers(rcc_device device, uint32_t prescalerSetupMask) {
	//clear mask
	registerClearValueInBitPosition (&device->CFGR, 0xFFF, 4);
	device->CFGR |= prescalerSetupMask;
}

void configureRCC_RTC_HSEPrescaler (rcc_device device, uint32_t rtcHSEPrescalerMask) {
	//clear mask
	registerClearValueInBitPosition (&device->CFGR, 0x1F, 16);
	device->CFGR |= rtcHSEPrescalerMask;
}

void configureRCC_RTC_BackUpDomainControl (rcc_device device, uint32_t rtcClockSelectFlag) {
	//clear mask
	registerClearValueInBitPosition (&device->BDCR, 0xFF, 8);
	registerClearValueInBitPosition (&device->BDCR, 0x1, 15);
	device->BDCR |= rtcClockSelectFlag;
}

void configureRCC_SystemClockSwitch (rcc_device device, uint8_t systemClockSwitchMask) {
	//clear mask
	//registerClearValueInBitPosition (&device->CR, 0x3, 0);
	registerClearValueInBitPosition (&device->CFGR, 0x3, 0);
	device->CFGR |= systemClockSwitchMask;
	if (systemClockSwitchMask == PLL_SYS_CLK_SWITCH) {
		waitForPLLSystemClockSwitch(device);
	}
	if (systemClockSwitchMask == HSE_SYS_CLK_SWITCH) {
		waitForHSESystemClockSwitch(device);
	}
}

void configureRCC_APB1_LowPowerModeClockSetting (rcc_device device, uint8_t apb1Device, uint8_t clockSettingFlag) {
	registerClearValueInBitPosition (&device->APB1LPENR, 0x1, apb1Device);
	registerSetValueInBitPosition (&device->APB1LPENR, clockSettingFlag, apb1Device);
}

void configureRCC_APB2_LowPowerModeClockSetting (rcc_device device, uint8_t apb2Device, uint8_t clockSettingFlag) {
	registerClearValueInBitPosition (&device->APB2LPENR, 0x1, apb2Device);
	registerSetValueInBitPosition (&device->APB2LPENR, clockSettingFlag, apb2Device);
}

void configureRCC_AHB1_LowPowerModeClockSetting (rcc_device device, uint8_t ahb1Device, uint8_t clockSettingFlag) {
	registerClearValueInBitPosition (&device->AHB1LPENR, 0x1, ahb1Device);
	registerSetValueInBitPosition (&device->AHB1LPENR, clockSettingFlag, ahb1Device);
}

void configureRCC_AHB2_LowPowerModeClockSetting (rcc_device device, uint8_t ahb2Device, uint8_t clockSettingFlag) {
	registerClearValueInBitPosition (&device->AHB2LPENR, 0x1, ahb2Device);
	registerSetValueInBitPosition (&device->AHB2LPENR, clockSettingFlag, ahb2Device);
}

void configureRCC_AHB3_LowPowerModeClockSetting (rcc_device device, uint8_t ahb3Device, uint8_t clockSettingFlag) {
	registerClearValueInBitPosition (&device->AHB3LPENR, 0x1, ahb3Device);
	registerSetValueInBitPosition (&device->AHB3LPENR, clockSettingFlag, ahb3Device);
}

void configureRCC_DedicatedClockSourceRegisterOne(rcc_device device, uint8_t deviceNumber,
		uint16_t deviceNumberMask, uint8_t deviceClockSource) {
	registerClearValueInBitPosition (&device->DCKCFGR1, deviceNumberMask, deviceNumber);
	registerSetValueInBitPosition (&device->DCKCFGR1, deviceClockSource, deviceNumber);
}

void configureRCC_DedicatedClockSourceRegisterTwo(rcc_device device, uint8_t deviceNumber,
		uint16_t deviceNumberMask, uint8_t deviceClockSource) {
	registerClearValueInBitPosition (&device->DCKCFGR2, deviceNumberMask, deviceNumber);
	registerSetValueInBitPosition (&device->DCKCFGR2, deviceClockSource, deviceNumber);
}

