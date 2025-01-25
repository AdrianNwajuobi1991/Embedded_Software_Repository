/*
 * USART_Dependency_Injection.h
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */

#ifndef USART_DEPENDENCY_INJECTION_H_
#define USART_DEPENDENCY_INJECTION_H_

#include "USART_Driver.h"

enum {
	USART_INSTANCE_3=3,USART_INSTANCE_5=5, USART_INSTANCE_4=4, USART_INSTANCE_2=2
};


usart_device getUSARTDeviceInstance (int instance);

void USARTDeviceCleanUp (usart_device device, USART_Config * usartConfig);

void Wait_For_TXE_Flag (usart_device device);

void Wait_For_TC_Flag (usart_device device);

void Wait_For_RXNE_Flag (usart_device device);

void initialize_USART4_Device (void);

void initialize_USART2_Device (void);

void initialize_USART3_Device (void);

void initialize_USART3_Device (void);

void initialize_USART5_Device (void);


#endif /* USART_DEPENDENCY_INJECTION_H_ */
