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
#include "FLASHDriverTest.h"
#include "RCCDriverTests.h"
#include "PWRDriverTest.h"
#include "RTC_Driver_Test.h"

static void run_SPI_Test_Group(void);
static void run_GPIO_Test_Group(void);
static void run_register_Bit_Utils_Test_Group (void);
static void run_I2C_Test_Group(void);
static void run_USART_Test_Group(void);
static void run_TIMER_Test_Group(void);
static void run_DMA_Test_Group(void);
static void run_FLASH_Test_Group (void);
static void run_RCC_Test_Group (void);
static void run_PWR_Test_Group (void);
static void run_RTC_Test_Group (void);

int main(void) {
	UNITY_BEGIN();

	//run_GPIO_Test_Group();

	//run_SPI_Test_Group();

	//run_register_Bit_Utils_Test_Group();

	//run_I2C_Test_Group();

	//run_USART_Test_Group();

	// run_TIMER_Test_Group();

	//run_FLASH_Test_Group();

	//run_DMA_Test_Group();

	//run_RCC_Test_Group();

	run_PWR_Test_Group();

	//run_RTC_Test_Group();

	return UNITY_END();
}


static void run_RTC_Test_Group (void) {
	RUN_TEST(test_RTC_Device_RESET_STATE);
	RUN_TEST(RTC_Initialize_Async_Sync_Prescalers_ASYNC_124_SYNC_7999);
	RUN_TEST(test_RTC_Initialization_12_HR_TIME_FORMAT_AM_Set_Date_Time_TO_12_26_24_4_11_30_WDU_4);
	RUN_TEST(test_RTC_Date_Time_Readout_12_26_24_4_11_30_WDU_4);
	RUN_TEST(test_RTC_GET_TIME_FORMAT_AS_12_HR_AND_GET_AM_FLAG);
}

static void run_PWR_Test_Group (void) {
	RUN_TEST(test_PWR_OverDrive_Enable);
	RUN_TEST(test_PWR_VOS_Set_Scale3);
	RUN_TEST(test_PWR_OverDriveSwitch_Enable);
	RUN_TEST(test_PWR_Enter_Stop_Mode_Main_Regulator_ON_AND_Flash_Memory_ON);
	RUN_TEST(test_PWR_Enter_Stop_Mode_Main_Regulator_ON_AND_Flash_Memory_POWER_DOWN);
	RUN_TEST(test_PWR_Enter_Stop_Mode_Low_Power_Regulator_ON_AND_Flash_Memory_ON);
	RUN_TEST(test_PWR_Enter_Stop_Mode_Low_Power_Regulator_ON_AND_Flash_Memory_OFF);
}

static void run_RCC_Test_Group (void) {
	RUN_TEST(test_216_MHZ_Core_Clock_Config_Main_PLLR_PLLQ_PLLP_PLLN_PLLM);
	RUN_TEST(test_select_HSE_AS_Main_PLL_Clock_source);
	RUN_TEST(test_RCC_HSE_Clock_Source_Enable_Main_PLL_HSE_BYPASS_Enable);
	RUN_TEST(test_RCC_MAIN_PLL_Enable_OTHER_PLLS_DISABLE);
	RUN_TEST(test_RCC_AHB_APB1_APB2_Prescalers_USE_DIV_4_AHB_DIV_8_APB1_DIV_16_APB2);
	RUN_TEST(test_system_Clock_Switch_To_PLL);
	RUN_TEST(test_RCC_Dedicated_Clocks_Config_Register_One_SAI2ClockSelect);
	RUN_TEST(test_RCC_RTC_HSE_Prescaler_DIV4);
	RUN_TEST(test_RTC_Clock_Source_Select_AND_ENABLE_RTC);
	RUN_TEST(test_RCC_APB_1_USART3_LPENR_Clock_Disable_In_Low_Power_Mode);
}


static void run_FLASH_Test_Group (void) {
	RUN_TEST(test_FLASH_Driver_Default_State);
	RUN_TEST(test_FLASH_Driver_Unlock_FLASH_Control_Register);
	RUN_TEST(test_FLASH_Driver_Lock_FLASH_Control_Register);
	RUN_TEST(test_FLASH_Driver_Progamming_Paralleism);
	RUN_TEST(test_FLASH_Driver_Sector_2_Erase);
	RUN_TEST(test_FLASH_Driver_Sector_2_3_4_Erase);
	RUN_TEST(test_FLASH_Driver_FLASH_Write);
	RUN_TEST(test_FLASH_Driver_Unlock_FLASH_Option_Register);
	RUN_TEST(test_FLASH_Driver_LATENCY_7WS_ART_ENABLE);
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
	RUN_TEST(test_USART_Configure_115200_baud_8DataBits_No_Parity_Bit_1StopBit_216MHZ_Clock_16X_Oversampling_No_DMA_No_Interupts);
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
	RUN_TEST(test_TIMER_Toggle_Output_Compare_Channel_1_Active_High_Polarity_500HZ_Output_Signal);
}
