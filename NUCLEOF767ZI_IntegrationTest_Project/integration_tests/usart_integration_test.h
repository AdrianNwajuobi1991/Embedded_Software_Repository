/*
 * spi_integration_test.h
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#ifndef USART_INTEGRATION_TEST_H_
#define USART_INTEGRATION_TEST_H_

#include "USART_Driver.h"

usart_device getUsartDevice (void);
void test_tx_send_long_string (void);
void test_tx_rx_basic_prompt (void);
void setup_usart_integration_test (void);
void test_tx_send_long_string_circular_mode (void);
void test_usart2_rx_of_usart5_tx (void);
void delayUSART(int ms);

#endif
