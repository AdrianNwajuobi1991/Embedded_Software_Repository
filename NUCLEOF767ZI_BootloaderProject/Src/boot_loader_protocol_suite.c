/*
 * boot_loader_protocol_suite.c
 *
 *  Created on: Aug 22, 2024
 *      Author: root
 */
#include "boot_loader_protocol_suite.h"
#include "stm32f7xx.h"
#include "gpio_integration_test.h"

#define FLASH_APP_REGION_START	0x08008000U
#define FLASH_SIZE	2016 * 1024

#define BOOT_LOADER_VERSION			0x82
#define APP_ADDR_VALID				0x41
#define APP_ADDR_INVALID		    0x42
#define FLASH_ERASE_OK				0x51
#define FLASH_ERASE_ERROR		    0x52

static bool is_crc_valid (uint8_t * command_packet, uint32_t non_crc_portion_offset, uint32_t crc_expected);
static void send_ack_sequence(comms_device_t commsDevice, uint8_t length_next_packet);
static bool run_crc_sequence (uint8_t * command_packet, uint32_t length);
static uint8_t check_app_address (uint8_t * command_packet, uint32_t length);

void bl_get_version (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {
	uint8_t boot_loader_version = BOOT_LOADER_VERSION;
	if (run_crc_sequence(command_packet, length) == true) {
		send_ack_sequence(commsDevice, 1);
		//send the boot loader version to host peer
		Comms_Device_SendPacket(commsDevice, &boot_loader_version, sizeof(boot_loader_version));
	}
}

void bl_get_help (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {
	unsigned char help_message[]="Supported command IDs range from 1-8.";
	uint8_t help_message_size = (sizeof(help_message)/sizeof(help_message[0]));
	if (run_crc_sequence(command_packet, length) == true) {
		send_ack_sequence(commsDevice, help_message_size);
		// send the help message response to host peer
		Comms_Device_SendPacket(commsDevice, help_message, help_message_size);
	}
}

void bl_get_chip_id (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {
	uint16_t chip_id;
	chip_id = (uint16_t) DBGMCU->IDCODE & 0x0FFF;
	if (run_crc_sequence(command_packet, length) == true) {
		send_ack_sequence(commsDevice, sizeof(uint16_t));
		//send the chip id response to host peer
		Comms_Device_SendPacket(commsDevice, &chip_id, sizeof(chip_id));
	}
}

void bl_get_rdp_status (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

	uint8_t read_protection_status;
	read_protection_status = (uint8_t)((*(volatile uint32_t *)0x1FFF0000) >> 8);
	if (run_crc_sequence(command_packet, length) == true) {
		send_ack_sequence(commsDevice, sizeof(uint8_t));
		//send the flash read protection status to host peer
		Comms_Device_SendPacket(commsDevice, &read_protection_status, sizeof(read_protection_status));
	}
}

void bl_go_to_app_address (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

	uint8_t status = 0;
	if (run_crc_sequence(command_packet, length) == true) {
		send_ack_sequence(commsDevice, sizeof(status));
		if (check_app_address(command_packet, length) == APP_ADDR_VALID) {
			status = APP_ADDR_VALID;
			//send the app address status to host peer
			Comms_Device_SendPacket(commsDevice, &status, sizeof(status));
			uint32_t app_address = (*(uint32_t *)(command_packet + 2));
			run_application(app_address);
		}
		if (check_app_address(command_packet, length) == APP_ADDR_INVALID) {
			status = APP_ADDR_INVALID;
			//send the app address status to host peer
			Comms_Device_SendPacket(commsDevice, &status, sizeof(status));
		}
	}
}

void bl_flash_erase (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

	uint8_t flash_erase_status = 0;
	if (run_crc_sequence(command_packet, length) == true) {
		send_ack_sequence(commsDevice, sizeof(flash_erase_status));
		/*
		 * TODO: perform the flash erase operation
		 */
		flash_erase_status = FLASH_ERASE_OK;
		//send the flash erase status to host peer
		Comms_Device_SendPacket(commsDevice, &flash_erase_status, sizeof(flash_erase_status));
	}

}

void bl_mem_write (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

}

void bl_enable_read_write_protect (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

}

void run_application (uint32_t app_address) {
	turn_off_GREEN_LED_PORTB();
	uint32_t app_msp_base = *(volatile uint32_t *)app_address;
	__set_MSP(app_msp_base);
	SCB->VTOR = app_address;
	uint32_t reset_handler_ptr = *(volatile uint32_t *)(app_address+4);
	void (*app_reset_handler_function) (void) = (void (*) (void))reset_handler_ptr;
	app_reset_handler_function();
}

static void send_ack_sequence(comms_device_t commsDevice, uint8_t length_next_packet) {
	uint8_t crcResponse[2];
	crcResponse[0] = ACK;
	crcResponse[1] = length_next_packet;
	//send the ACK response and length of the data to follow
	Comms_Device_SendPacket(commsDevice, crcResponse, 2);
}

static uint8_t check_app_address (uint8_t * command_packet, uint32_t length) {
	uint32_t app_address = (*(uint32_t *)(command_packet + 2));
	if (app_address >= FLASH_APP_REGION_START && app_address < FLASH_APP_REGION_START+FLASH_SIZE) {
		return APP_ADDR_VALID;
	}
	return APP_ADDR_INVALID;
}

static bool run_crc_sequence (uint8_t * command_packet, uint32_t length) {
	uint32_t nonCRCPacketPortionLength = length-sizeof(uint32_t);
	uint32_t crc_expected = *(uint32_t *)(command_packet+nonCRCPacketPortionLength);
	if (is_crc_valid(command_packet, nonCRCPacketPortionLength, crc_expected) == true) {
		return true;
	}
	return false;
}

static bool is_crc_valid (uint8_t * command_packet, uint32_t non_crc_portion_offset, uint32_t crc_expected) {
	return (crc_expected == 0xABDE7C98);
	//return true;
}

