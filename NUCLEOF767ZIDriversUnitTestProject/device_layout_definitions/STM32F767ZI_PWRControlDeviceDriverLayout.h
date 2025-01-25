/*
 * STM32F767ZI_PWRControlDeviceDriverLayout.h
 *
 *  Created on: Nov 4, 2024
 *      Author: root
 */

#ifndef STM32F767ZI_PWRCONTROLDEVICEDRIVERLAYOUT_H_
#define STM32F767ZI_PWRCONTROLDEVICEDRIVERLAYOUT_H_

#include <stdint.h>

#define __IO volatile

typedef struct PWR_TypeDef_t
{
  __IO uint32_t CR1;   /*!< PWR power control register 1,        Address offset: 0x00 */
  __IO uint32_t CSR1;  /*!< PWR power control/status register 2, Address offset: 0x04 */
  __IO uint32_t CR2;   /*!< PWR power control register 2,        Address offset: 0x08 */
  __IO uint32_t CSR2;  /*!< PWR power control/status register 2, Address offset: 0x0C */
} PWR_TypeDef_t;


#endif /* STM32F767ZI_PWRCONTROLDEVICEDRIVERLAYOUT_H_ */
