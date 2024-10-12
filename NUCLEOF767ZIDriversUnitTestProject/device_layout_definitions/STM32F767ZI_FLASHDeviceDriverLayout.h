/*
 * STM32F767ZI_FLASHDeviceDriverLayout.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef STM32F767ZI_FLASHDEVICEDRIVERLAYOUT_H_
#define STM32F767ZI_FLASHDEVICEDRIVERLAYOUT_H_

#include <stdint.h>

#define __IO volatile

typedef struct FLASH_TypeDef_t
{
  __IO uint32_t ACR;      /*!< FLASH access control register,     Address offset: 0x00 */
  __IO uint32_t KEYR;     /*!< FLASH key register,                Address offset: 0x04 */
  __IO uint32_t OPTKEYR;  /*!< FLASH option key register,         Address offset: 0x08 */
  __IO uint32_t SR;       /*!< FLASH status register,             Address offset: 0x0C */
  __IO uint32_t CR;       /*!< FLASH control register,            Address offset: 0x10 */
  __IO uint32_t OPTCR;    /*!< FLASH option control register ,    Address offset: 0x14 */
  __IO uint32_t OPTCR1;   /*!< FLASH option control register 1 ,  Address offset: 0x18 */
} FLASH_TypeDef_t;

#endif /* STM32F767ZI_FLASHDEVICEDRIVERLAYOUT_H_ */
