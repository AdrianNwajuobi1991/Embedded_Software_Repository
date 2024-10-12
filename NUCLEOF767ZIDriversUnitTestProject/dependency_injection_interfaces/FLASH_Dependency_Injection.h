/*
 * FLASH_Device_Dependency_Injection.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef FLASH_DEPENDENCY_INJECTION_H_
#define FLASH_DEPENDENCY_INJECTION_H_

#include "STM32F767ZI_FLASHDeviceDriverLayout.h"
#include "FLASH_Driver.h"


flash_device getFlashDeviceInstance (void);

void FlashDeviceInstanceCleanUp (void);



#endif /* FLASH_DEPENDENCY_INJECTION_H_ */
