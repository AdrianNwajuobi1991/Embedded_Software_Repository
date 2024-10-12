/*
 * USARTDriverTest.h
 *
 *  Created on: Aug 18, 2024
 *      Author: root
 */

#ifndef USARTDRIVERTEST_H_
#define USARTDRIVERTEST_H_

void test_USART_Instance_Has_Default_Values (void);
void test_USART_Enable_NO_DMA_NO_Interrupts (void);
void test_USART_Disable_NO_DMA_NO_Interrupts (void);
void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_Error_Interrupt (void);
void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_TX_Interrupt (void);
void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_RX_Interrupt (void);
void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_No_Interupts (void);
void test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_8X_Oversampling_No_DMA_No_Interupts (void);

#endif /* USARTDRIVERTEST_H_ */
