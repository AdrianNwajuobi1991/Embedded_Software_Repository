/*
 * USART_Dependency_Injection_Container.c
 *
 *  Created on: Aug 19, 2024
 *      Author: root
 */
#include "stm32f7xx.h"
#include "USART_Dependency_Injection.h"
#include "GPIO_Dependency_Injection.h"
#include "STM32F767ZI_USARTDeviceDriverLayout.h"
#include "register_bit_utils.h"

#define TXE_BITPOS			7
#define RXNE_BITPOS			5
#define TC_BITPOS			6
#define USART3EN_BITPOS		18
#define USART3SEL_BITPOS	4
#define USART5EN_BITPOS		20
#define USART5SEL_BITPOS	8

usart_device getUSARTDeviceInstance (int instance) {
	volatile uint32_t * CPACR = (volatile uint32_t *)0xE000ED88;
	*CPACR |= (0x3 << 22)|(0x3 << 20);

	if (instance == USART_INSTANCE_5) {
		return (usart_device)UART5_BASE;
	}
	if (instance == USART_INSTANCE_3) {
		return (usart_device)USART3_BASE;
	}
}

void Wait_For_TXE_Flag (usart_device device) {
	while (registerTestBitPosition (&device->ISR, TXE_BITPOS) != BIT_SET) {}
}

void Wait_For_TC_Flag (usart_device device) {
	while (registerTestBitPosition (&device->ISR, TC_BITPOS) != BIT_SET) {}
}

void Wait_For_RXNE_Flag (usart_device device) {
	while (registerTestBitPosition (&device->ISR, RXNE_BITPOS) != BIT_SET) {}
}

void initialize_USART3_Device (void) {
	initialize_GPIO_PORTD();
	registerSetBit(&RCC->APB1ENR, USART3EN_BITPOS);
	registerSetValueInBitPosition (&RCC->DCKCFGR2, 1, USART3SEL_BITPOS);
}

void initialize_USART5_Device (void) {
	initialize_GPIO_PORTB();
	registerSetBit(&RCC->APB1ENR, USART5EN_BITPOS);
	registerSetValueInBitPosition (&RCC->DCKCFGR2, 1, USART5SEL_BITPOS);
}

void USARTDeviceCleanUp (usart_device device, USART_Config * usartConfig) {

}
