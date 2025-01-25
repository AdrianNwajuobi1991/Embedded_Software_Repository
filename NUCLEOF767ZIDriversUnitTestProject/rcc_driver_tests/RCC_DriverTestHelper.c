/*
 * RCC_DriverTestHelper.c
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#include "RCC_DriverTestHelper.h"
#include "STM32F767ZI_RCCDeviceDriverLayout.h"
#include "RCC_Driver.h"
#include "register_bit_utils.h"

uint32_t getRCC_PLCFGRRegisterValue(rcc_device rccDevice) {
	return registerGetValue(&rccDevice->PLLCFGR);
}

uint32_t getRCC_CRRegisterValue (rcc_device rccDevice) {
	return registerGetValue(&rccDevice->CR);
}

uint32_t getRCC_CFGRRegisterValue (rcc_device rccDevice) {
	return registerGetValue(&rccDevice->CFGR);
}

uint32_t getRCC_DCKCFGR1RegisterValue (rcc_device rccDevice) {
	return registerGetValue(&rccDevice->DCKCFGR1);
}

uint32_t getRCC_BDCRRegisterValue (rcc_device device) {
	return device->BDCR;
}

uint32_t getRCC_APB1LPENRRegisterValue (rcc_device rccDevice) {
	return rccDevice->APB1LPENR;
}
