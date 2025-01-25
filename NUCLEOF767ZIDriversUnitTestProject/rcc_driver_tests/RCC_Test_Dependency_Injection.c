/*
 * RCC_Test_Dependency_Injection.c
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#include "STM32F767ZI_RCCDeviceDriverLayout.h"
#include "RCC_Driver.h"
#include "RCC_Dependency_Injection.h"

static RCC_TypeDef_t rccDevice;

rcc_device getRCCDeviceInstance (void) {
	rcc_device device = &rccDevice;
	rccDevice.PLLCFGR = 0x24003010;
	rccDevice.CFGR = 0x00000000;
	rccDevice.CR = 0x00000083;
	rccDevice.APB1LPENR = 0xFFFFEFFF;
	return device;
}

void RCC_DeviceInstanceCleanUp (void) {
	rccDevice.PLLCFGR = 0x24003010;
	rccDevice.CFGR = 0x00000000;
	rccDevice.CR = 0x00000083;
	rccDevice.APB1LPENR = 0xFFFFEFFF;
}


void waitForHSEClockRDY (rcc_device device) {

}

void waitForMainPLLRDY (rcc_device device) {

}

void waitForI2SPLLRDY (rcc_device device) {

}

void waitForSAIPLLRDY (rcc_device device) {

}

void waitForPLLSystemClockSwitch (rcc_device device) {

}

void waitForHSESystemClockSwitch (rcc_device device) {

}
