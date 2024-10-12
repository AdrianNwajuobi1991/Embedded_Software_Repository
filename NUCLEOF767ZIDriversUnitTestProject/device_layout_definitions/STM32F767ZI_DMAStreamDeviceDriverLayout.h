/*
 * STM32F767ZI_DMAStreamDeviceLayout.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef STM32F767ZI_DMASTREAMDEVICEDRIVERLAYOUT_H_
#define STM32F767ZI_DMASTREAMDEVICEDRIVERLAYOUT_H_

#include <stdint.h>

#define __IO volatile

typedef struct DMA_Stream_TypeDef_t
{
  __IO uint32_t CR;     /*!< DMA stream x configuration register      */
  __IO uint32_t NDTR;   /*!< DMA stream x number of data register     */
  __IO uint32_t PAR;    /*!< DMA stream x peripheral address register */
  __IO uint32_t M0AR;   /*!< DMA stream x memory 0 address register   */
  __IO uint32_t M1AR;   /*!< DMA stream x memory 1 address register   */
  __IO uint32_t FCR;    /*!< DMA stream x FIFO control register       */
} DMA_Stream_TypeDef_t;

typedef struct DMA_TypeDef_t
{
  __IO uint32_t LISR;   /*!< DMA low interrupt status register,      Address offset: 0x00 */
  __IO uint32_t HISR;   /*!< DMA high interrupt status register,     Address offset: 0x04 */
  __IO uint32_t LIFCR;  /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
  __IO uint32_t HIFCR;  /*!< DMA high interrupt flag clear register, Address offset: 0x0C */
} DMA_TypeDef_t;

#endif /* STM32F767ZI_DMASTREAMDEVICEDRIVERLAYOUT_H_ */
