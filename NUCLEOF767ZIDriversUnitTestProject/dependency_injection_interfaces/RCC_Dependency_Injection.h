/*
 * RCC_Dependency_Injection.h
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#ifndef RCC_DEPENDENCY_INJECTION_H_
#define RCC_DEPENDENCY_INJECTION_H_

#include "RCC_Driver.h"

rcc_device getRCCDeviceInstance (void);

void RCC_DeviceInstanceCleanUp (void);

void waitForHSEClockRDY (rcc_device devices);

void waitForMainPLLRDY (rcc_device device);

void waitForI2SPLLRDY (rcc_device device);

void waitForSAIPLLRDY (rcc_device device);

void waitForMainPLLNotRDY (rcc_device device);

void waitForPLLSystemClockSwitch (rcc_device device);

void waitForHSESystemClockSwitch (rcc_device device);

#endif /* RCC_DEPENDENCY_INJECTION_H_ */
