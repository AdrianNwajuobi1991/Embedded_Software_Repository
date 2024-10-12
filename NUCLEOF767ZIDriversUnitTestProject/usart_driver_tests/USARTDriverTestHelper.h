/*
 * USARTDriverTestHelper.h
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */

#ifndef USARTDRIVERTESTHELPER_H_
#define USARTDRIVERTESTHELPER_H_

#include <stdint.h>
#include "USART_Driver.h"


uint32_t getUSARTDeviceBRRValue (usart_device device);
uint32_t getUSARTDeviceCR1Value (usart_device device);
uint32_t getUSARTDeviceCR2Value (usart_device device);
uint32_t getUSARTDeviceCR3Value (usart_device device);
uint32_t getUSARTDeviceISRValue (usart_device device);
uint32_t getUSARTDeviceICRValue (usart_device device);

#endif /* USARTDRIVERTESTHELPER_H_ */
