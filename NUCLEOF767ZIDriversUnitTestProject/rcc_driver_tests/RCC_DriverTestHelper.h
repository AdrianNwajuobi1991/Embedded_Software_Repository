/*
 * RCC_DriverTestHelper.h
 *
 *  Created on: Oct 31, 2024
 *      Author: root
 */

#ifndef RCC_DRIVERTESTHELPER_H_
#define RCC_DRIVERTESTHELPER_H_

#include "RCC_Driver.h"
#include <stdint.h>

uint32_t getRCC_PLCFGRRegisterValue (rcc_device rccDevice);

uint32_t getRCC_CRRegisterValue (rcc_device rccDevice);

uint32_t getRCC_CFGRRegisterValue (rcc_device rccDevice);

uint32_t getRCC_DCKCFGR1RegisterValue (rcc_device rccDevice);

uint32_t getRCC_BDCRRegisterValue (rcc_device rccDevice);

uint32_t getRCC_APB1LPENRRegisterValue (rcc_device rccDevice);

#endif /* RCC_DRIVERTESTHELPER_H_ */
