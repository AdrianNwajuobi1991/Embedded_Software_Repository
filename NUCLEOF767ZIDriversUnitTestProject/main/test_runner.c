/*
 ============================================================================
 Name        : NUCLEOF767ZIGPIODriverTestProject.c
 Author      : Adrian Nwajuobi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "unity.h"

#include "GPIODriverTests.h"
#include "SPIDriverTest.h"
#include "registerBitUtilsTest.h"
#include "I2CDriverTest.h"
#include "USARTDriverTest.h"
#include "DMADriverTest.h"
#include "TIMERDriverTest.h"

static void run_SPI_Test_Group(void);
static void run_GPIO_Test_Group(void);
static void run_register_Bit_Utils_Test_Group (void);
static void run_I2C_Test_Group(void);
static void run_USART_Test_Group(void);
static void run_TIMER_Test_Group(void);
static void run_DMA_Test_Group(void);

int main(void) {
	UNITY_BEGIN();

	//run_GPIO_Test_Group();

	//run_SPI_Test_Group();

	//run_register_Bit_Utils_Test_Group();

	//run_I2C_Test_Group();

	//run_USART_Test_Group();

	run_TIMER_Test_Group();

	//run_DMA_Test_Group();

	return UNITY_END();
}

static void run_DMA_Test_Group(void) {
	RUN_TEST (test_DMA_STREAM_Device_Default_State);
	RUN_TEST (test_MEMORY_TO_MEMORY_Transfer_4_NDT_PSIZE_AND_MSIZE_OF_2_BYTES_FIFO_ENABLED);
	RUN_TEST (test_MEMORY_TO_PERIPHERAL_Transfer_4_NDT_PSIZE_AND_MSIZE_OF_2_BYTES_FIFO_ENABLED);
	RUN_TEST (test_PERIPHERAL_TO_MEMORY_Transfer_4_NDT_PSIZE_AND_MSIZE_OF_2_BYTES_FIFO_ENABLED);
}

static void run_GPIO_Test_Group(void) {
	RUN_TEST (test_GPIODriverCreationGPIOPORTAANDBInstances);
	RUN_TEST (test_GPIODriverGPIOPORTAConfigureMODEToGPIOOperation);
	RUN_TEST (test_GPIODriverGPIOPORTBConfigureMODEToGPIOOperation);
	RUN_TEST (test_GPIOPORTAConfigureMODEToAlternateFunctionOperation);
	RUN_TEST (test_GPIOPORTBConfigureMODEToAlternateFunctionOperation);
	RUN_TEST (test_GPIOPORTAConfigureOutputTypeToOpenDrain);
	RUN_TEST (test_GPIOPORTBConfigureOutputTypeToOpenDrain);
	RUN_TEST (test_GPIOPORTAConfigureOutputSpeed);
	RUN_TEST (test_GPIOPORTAConfigureOutputSpeedTwoDifferentSpeedsSamePin);
	RUN_TEST (test_GPIOPORTBConfigureOutputSpeed);
	RUN_TEST (test_GPIOPORTAConfigureForPullUp);
	RUN_TEST (test_GPIOPORTBConfigureForPullDown);
	RUN_TEST (test_GPIOPORTAReadInputDataRegister);
	RUN_TEST (test_GPIOPORTBReadInputDataRegister);
	RUN_TEST (test_GPIOPORTABitSetResetRegisterSetPIN6);
	RUN_TEST (test_GPIOPORTABitSetResetRegisterResetPIN6);
	RUN_TEST (test_GPIOPORTBBitSetResetRegisterSetPIN6);
	RUN_TEST (test_GPIOPORTBBitSetResetRegisterResetPIN6);
	RUN_TEST (test_GPIOPORTAAlternateFunctionLowRegisterPIN2AlternateFunction);
	RUN_TEST (test_GPIOPORTAAlternateFunctionHighRegisterPIN10AlternateFunction);
	RUN_TEST (test_GPIOPORTBAlternateFunctionLowRegisterPIN2AlternateFunction);
	RUN_TEST (test_GPIOPORTBAlternateFunctionHighRegisterPIN10AlternateFunction);
	RUN_TEST (test_GPIOPORTBAlternateFunctionHighRegisterPIN14PIN15Simultaneous);
	RUN_TEST (test_GPIOPORTB_SetGPIO_PORTB_TO_GIVEN_VALUE);
	RUN_TEST (test_GPIOPORTB_ClearGPIO_PORTB_OF_GIVEN_VALUE);
}

static void run_SPI_Test_Group(void) {
	RUN_TEST (test_GetSPIInstance_Instance_Has_Default_Values);
	RUN_TEST (test_Config_Master_Mode_One_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter);
	RUN_TEST (test_Config_Slave_Mode_One_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter);
	RUN_TEST (test_Config_Slave_Mode_Three_FullDuplex_2MHZ_MSBFirst_SSM_Disabled_8BitData_FiFoThreshold_Quarter);
}

static void run_register_Bit_Utils_Test_Group (void) {
	RUN_TEST (testSetBitInRegister);
	RUN_TEST (testClearBitInRegister);
	RUN_TEST (testToggleBitInRegister);
	RUN_TEST (testBitValueInRegister);
	RUN_TEST (testSetValueInBitPositionInRegister);
	RUN_TEST (testClearValueInBitPositionInRegister);
	RUN_TEST (testToggleValueInBitPositionInRegister);
	RUN_TEST (testMaskBitsInRegister);
	RUN_TEST (testOverwriteValueInRegister);
	RUN_TEST (testGetValueOfRegister);
}

static void run_I2C_Test_Group (void) {
	RUN_TEST(test_I2C_RegisterValuesAreCorrectDefaults);
	RUN_TEST(test_I2C_StandardMode_FI2CCLK16MHZ_100KHZ_SPEED_AFON_DNF_15X);
	RUN_TEST(test_I2C_EnableDevice);
	RUN_TEST(test_I2C_Master_TransmitLessthan255_Bytes_NO_RELOAD_NO_REPEATED_START);
}

static void run_USART_Test_Group(void) {
	RUN_TEST(test_USART_Instance_Has_Default_Values);
	RUN_TEST(test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_Error_Interrupt);
	RUN_TEST(test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_TX_Interrupt);
	RUN_TEST(test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_RX_Interrupt);
	RUN_TEST(test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_16X_Oversampling_No_DMA_No_Interupts);
	RUN_TEST(test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_16MHZ_Clock_8X_Oversampling_No_DMA_No_Interupts);
	RUN_TEST(test_USART_Enable_NO_DMA_NO_Interrupts);
	RUN_TEST(test_USART_Disable_NO_DMA_NO_Interrupts);
}

static void run_TIMER_Test_Group(void) {
	RUN_TEST(test_TIMER_Default_Register_Values);
	RUN_TEST(test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_NON_INVERTED_BOTH_ENABLED);
	RUN_TEST(test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_NON_INVERTED_BOTH_DISABLED);
	RUN_TEST(test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_INVERTED_BOTH_ENABLED);
	RUN_TEST(test_PWM_OUTPUT_ACTIVATION_CHANNEL1_AND_2_INVERTED_BOTH_DISABLED);
	RUN_TEST(test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI1_8_Samples_NO_INTERRUPTS);
	RUN_TEST(test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI1_NO_Samples_NO_PRESCALER_Allow_INTERRUPTS_NO_DMA);
	RUN_TEST(test_TIMER_INPUT_CAPTURE_RISING_EDGE_DIRECT_ONLY_TI4_NO_Samples_NO_PRESCALER_Allow_INTERRUPTS_NO_DMA);
	RUN_TEST(test_Timer_OR_Register_Choose_LSE_Oscillator_Option);
	RUN_TEST(test_Encoder_Mode_Setup);
	RUN_TEST(test_TIMER_INTERRUPTS_Config_DIER_REGISTER_ALL_INTERRUPTS_ENABLED);
	RUN_TEST(test_TIME_BASE_UNIT_200MS_32_BIT_TIMER_FCK_CNT_1MHZ_TIM_RCC_CLK_16MHZ);
	RUN_TEST(test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_NON_INVERTING_BOTH_ACTIVE_LOW);
	RUN_TEST(test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_INVERTING_BOTH_ACTIVE_LOW);
	RUN_TEST(test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_NON_INVERTING_BOTH_ACTIVE_LOW);
	RUN_TEST(test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_INVERTING_BOTH_ACTIVE_HIGH);
	RUN_TEST(test_20KHZ_PWM_FREQUENCY_TIMER_DUTY_CYCLE_50_PERCENT_UP_COUNTING_EDGE_ALIGNED_INPUT_CLOCK_16MHZ_INTERNAL_OUTPUT_ON_CHANNEL_1_AND_CHANNEL_2_NON_INVERTING_BOTH_ACTIVE_HIGH);
}
