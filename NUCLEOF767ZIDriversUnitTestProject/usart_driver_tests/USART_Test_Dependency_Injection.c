/*
 * USART_Test_Dependency_Injection.c
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */

#include "USART_Dependency_Injection.h"
#include "STM32F767ZI_USARTDeviceDriverLayout.h"

static USART_TypeDef_t usartDevices [3];

usart_device getUSARTDeviceInstance (int instance) {
	usartDevices[instance].BRR = 0x00000000;
	usartDevices[instance].CR1 = 0x00000000;
	usartDevices[instance].CR2 = 0x00000000;
	usartDevices[instance].CR3 = 0x00000000;
	usartDevices[instance].ISR = 0x020000C0;
	usartDevices[instance].ICR = 0x00000000;
	return &usartDevices[instance];
}

void Wait_For_TXE_Flag (usart_device device) {
	return;
}

void Wait_For_TC_Flag (usart_device device) {
	return;
}

void Wait_For_RXNE_Flag (usart_device device) {
	return;
}

void initialize_USART3_Device (void) {
	return;
}

void USARTDeviceCleanUp (usart_device device, USART_Config * usartConfig) {
	device->BRR = 0;
	device->CR1 = 0;
	device->CR2 = 0;
	device->CR3 = 0;
	device->ISR = 0x020000C0;
	device->ICR = 0x00000000;
}
