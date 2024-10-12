/*
 * spi_integration_test.c
 *
 *  Created on: Jul 30, 2024
 *      Author: root
 */

#include "SPI_Dependency_Injection.h"
#include "GPIO_Dependency_Injection.h"
#include "gpio_integration_test.h"
#include "spi_integration_test.h"
#include <string.h>

static spi_device spiDevice1 = 0;
static gpio_device ADXL345_GPIO_PORT = 0;

void test_tx_only_Arduino_Slave (void) {
	uint8_t txPacket[2];
	uint8_t rxPacket[2];
	char test_packet[] = "Ichigo's Bankai is Tensa Zangetsu!";
	uint32_t packetLength = strlen(test_packet);
	uint8_t junk_packet[packetLength];
	txPacket[0] = packetLength;
	txPacket[1] = 0xFF;

	spi_manual_slave_select(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
	spi_transceive_packet_bytes(spiDevice1, txPacket, rxPacket, 2);
	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);

	spi_manual_slave_select(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
	spi_transceive_packet_bytes(spiDevice1, (uint8_t *)test_packet, junk_packet, packetLength);
	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
}

void test_CMD_Arduino_Slave_LED_CTRL (void) {
	uint8_t led_ctrl_cmd = 0x50;
	uint8_t led_ctrl_cmd_dummy = 0xFF;
	uint8_t ack_nack_result = 0xFF;

	uint8_t led_pin_number = 1;
	uint8_t led_value = 1;

	uint8_t ACK = 0xF5;
	uint8_t LED_ARGS[2];
	uint8_t LED_ARGS_DUMMY[2];
	LED_ARGS[0] = led_pin_number;
	LED_ARGS[1] = led_value;
	//uint8_t NACK = 0xA5;

	spi_manual_slave_select(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
	spi_transceive_packet_bytes(spiDevice1, &led_ctrl_cmd, &led_ctrl_cmd_dummy, 1);
	spi_transceive_packet_bytes(spiDevice1, &led_ctrl_cmd_dummy, &ack_nack_result, 1);

	if (ack_nack_result == ACK) {
		turn_on_BLUE_LED_PORTB();
	}else{
		turn_on_RED_LED_PORTB();
	}
	spi_transceive_packet_bytes(spiDevice1, LED_ARGS, LED_ARGS_DUMMY, 2);
	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
}

void test_get_ADXL345_Device_ID (void) {
	uint8_t txPacket[2];
	uint8_t rxPacket[2];
	txPacket[0] = 0x80;
	txPacket[1] = 0xFF;

	spi_manual_slave_select(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
	spi_transceive_packet_bytes(spiDevice1, txPacket, rxPacket, 2);
	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);

	if (rxPacket[1] == 0xE5) {
		turn_on_GREEN_LED_PORTB();
	}
}

void test_set_ADXL345_Power_CTL_Registers (void) {
	uint8_t txPacket[2];
	uint8_t rxPacket[2];
	txPacket[0] = 0x2D;
	txPacket[1] = (1 << 3);

	spi_manual_slave_select(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
	spi_transceive_packet_bytes(spiDevice1, txPacket, rxPacket, 2);
	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
}

void test_read_ADXL345_Power_CTL_Registers (void) {
	uint8_t txPacket[2];
	uint8_t rxPacket[2];
	txPacket[0] = 0x2D|(1 << 7);
	txPacket[1] = 0xFF;

	spi_manual_slave_select(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
	spi_transceive_packet_bytes(spiDevice1, txPacket, rxPacket, 2);
	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);

	if (rxPacket[1] == 0x08) {
		turn_on_BLUE_LED_PORTB();
	}
}

void test_set_ADXL345_BW_Rate_Registers (void) {
	uint8_t txPacket[2];
	uint8_t rxPacket[2];
	txPacket[0] = 0x2C;
	txPacket[1] = 0x0A;

	spi_manual_slave_select(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
	spi_transceive_packet_bytes(spiDevice1, txPacket, rxPacket, 2);
	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);
}


void setup_spi_master_integration_test (uint8_t spi_mode) {
	spiDevice1 = getSPIDeviceInstance(SPI_INSTANCE_1);
	ADXL345_GPIO_PORT = getGPIODeviceInstance(PORTA);
	initialize_SPI_Device_One();
	GPIOPortConfiguration gpioConfigADXL345_GPIO_PORT;

	memset(&gpioConfigADXL345_GPIO_PORT, 0, sizeof(gpioConfigADXL345_GPIO_PORT));

	gpioConfigADXL345_GPIO_PORT.gpioModeConfiguration = ALT_FUNC_MODE;
	gpioConfigADXL345_GPIO_PORT.gpioOutputSpeedConfiguration = VERY_HIGH_SPEED;
	gpioConfigADXL345_GPIO_PORT.gpioOutputTypeConfiguration = PUSH_PULL;
	gpioConfigADXL345_GPIO_PORT.gpioPUPDConfiguration = NO_PULLUP_PULLDOWN;
	gpioConfigADXL345_GPIO_PORT.gpioAFRLConfiguration = AF5; //SPI1 functions

	configureGPIODevice(ADXL345_GPIO_PORT, &gpioConfigADXL345_GPIO_PORT, PIN5); //SCK
	configureGPIODevice(ADXL345_GPIO_PORT, &gpioConfigADXL345_GPIO_PORT, PIN6); //MISO
	configureGPIODevice(ADXL345_GPIO_PORT, &gpioConfigADXL345_GPIO_PORT, PIN7); //MOSI

	gpioConfigADXL345_GPIO_PORT.gpioModeConfiguration = GENERAL_PURPOSE_OUTPUT;
	gpioConfigADXL345_GPIO_PORT.gpioAFRLConfiguration = AF0; //SPI1 functions

	configureGPIODevice(ADXL345_GPIO_PORT, &gpioConfigADXL345_GPIO_PORT, SLAVE_SELECT_PIN); //CS Line

	spi_manual_slave_release(ADXL345_GPIO_PORT, SLAVE_SELECT_PIN);

	SPI_HalfDuplex_Config halfDuplexConfig = {0};
	SPI_Config config;
	config.spi_device_role = SPI_MASTER;
	config.spi_device_mode = spi_mode;
	config.spi_baud_rate = DEFAULT_PCLK_DIV8;
	config.byte_order = MSB_FIRST;
	config.slave_mangement_mode = SOFTWARE_SLAVE_MANAGEMENT;
	config.data_size = EIGHT_BITS;
	config.transciever_setting = FULL_DUPLEX;
	config.half_duplex_config = halfDuplexConfig;

	configureSPIDevice (spiDevice1, &config);
	enable_spi_device (spiDevice1);

}
