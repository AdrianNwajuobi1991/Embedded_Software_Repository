/*
 * TimerDriverTest.h
 *
 *  Created on: Aug 24, 2024
 *      Author: root
 */

#ifndef TIMERDRIVERTEST_H_
#define TIMERDRIVERTEST_H_

void test_TIMER_Default_Register_Values (void);
void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_NON_INVERTED_BOTH_ENABLED (void);
void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_NON_INVERTED_BOTH_DISABLED (void);
void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_INVERTED_BOTH_ENABLED (void);
void test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_INVERTED_BOTH_DISABLED (void);
void test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI1_8_Samples_NO_INTERRUPTS (void);
void test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI1_NO_Samples_NO_PRESCALER_Allow_INTERRUPTS_NO_DMA (void);
void test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI4_NO_Samples_NO_PRESCALER_Allow_INTERRUPTS_NO_DMA (void);
void test_Timer_OR_Register_Choose_LSE_Oscillator_Option (void);
void test_Encoder_Mode_Setup (void);
void test_TIMER_INTERRUPTS_Config_DIER_REGISTER_ALL_INTERRUPTS_ENABLED (void);
void test_TIME_BASE_UNIT_200MS_32_BIT_TIMER_FCK_CNT_1MHZ_TIM_RCC_CLK_16MHZ (void);
void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_INVERTING_BOTH_ACTIVE_LOW (void);
void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_NON_INVERTING_BOTH_ACTIVE_LOW (void);
void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_INVERTING_BOTH_ACTIVE_HIGH (void);
void test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_NON_INVERTING_BOTH_ACTIVE_HIGH (void);

#endif /* TIMERDRIVERTEST_H_ */