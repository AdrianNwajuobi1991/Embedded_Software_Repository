/*
 * USARTDriverTestHelper.c
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */


#include "USARTDriverTestHelper.h"
#include "register_bit_utils.h"
#include "USART_Driver.h"
#include "STM32F767ZI_USARTDeviceDriverLayout.h"

uint32_t getUSARTDeviceBRRValue (usart_device device) {
	return registerGetValue(&device->BRR);
}
uint32_t getUSARTDeviceCR1Value (usart_device device) {
	return registerGetValue(&device->CR1);
}
uint32_t getUSARTDeviceCR2Value (usart_device device) {
	return registerGetValue(&device->CR2);
}
uint32_t getUSARTDeviceCR3Value (usart_device device) {
	return registerGetValue(&device->CR3);
}
uint32_t getUSARTDeviceISRValue (usart_device device) {
	return registerGetValue(&device->ISR);
}
uint32_t getUSARTDeviceICRValue (usart_device device) {
	return registerGetValue(&device->ICR);
}
