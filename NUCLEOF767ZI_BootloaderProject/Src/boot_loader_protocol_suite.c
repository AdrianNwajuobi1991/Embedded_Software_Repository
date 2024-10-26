/*
 * boot_loader_protocol_suite.c
 *
 *  Created on: Aug 22, 2024
 *      Author: root
 */
#include "boot_loader_protocol_suite.h"
#include "stm32f7xx.h"
#include "gpio_integration_test.h"
#include "FLASH_Dependency_Injection.h"
#include "FLASH_Driver.h"
#include <string.h>
#include "gpio_integration_test.h"

#define FLASH_APP_REGION_START	0x08008000U
#define FLASH_SIZE	2016 * 1024

#define BOOT_LOADER_VERSION			0x82
#define APP_ADDR_VALID				0x41
#define APP_ADDR_INVALID		    0x42
#define FLASH_ERASE_OK				0x51
#define FLASH_ERASE_ERROR		    0x52
#define FLASH_WRITE_OK				0x53
#define FLASH_WRITE_ERROR		    0x54

static bool is_crc_valid (uint8_t * command_packet, uint32_t non_crc_portion_offset, uint32_t crc_expected);
static void send_ack_sequence(comms_device_t commsDevice, uint8_t length_next_packet);
static bool run_crc_sequence (uint8_t * command_packet, uint32_t length);
static uint8_t check_app_address (uint8_t * command_packet, uint32_t length);

extern flash_device flashDevice;
static volatile uint8_t * flash_app_write_address = (volatile uint8_t *)FLASH_APP_REGION_START;

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
		uint8_t sectorToErase = (*(command_packet + 2));
		flashSectorErase (flashDevice, sectorToErase);

		if (checkFlashOperationError (flashDevice, ERSERR) == true) {
			flash_erase_status = FLASH_ERASE_ERROR;
		}
		if (checkFlashOperationError (flashDevice, ERSERR) == false) {
			flash_erase_status = FLASH_ERASE_OK;
		}
		//send the flash erase status to host peer
		Comms_Device_SendPacket(commsDevice, &flash_erase_status, sizeof(flash_erase_status));
	}
}

void bl_mem_write (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

	uint8_t flash_write_status = 0;
	uint8_t flash_write_acknowledge = 0x33;
	uint8_t code_payload_packet[CODE_PACKET_SIZE];
	uint32_t number_of_code_payloads = 0;
	if (run_crc_sequence(command_packet, length) == true) {
		send_ack_sequence(commsDevice, sizeof(flash_write_status));
		/*
		 * TODO: perform the flash write operations
		 */
		/* receive the number of code payload packets */
		Comms_Device_RecvPacket(commsDevice, &number_of_code_payloads, sizeof(number_of_code_payloads));
		// send the flash write acknowledge to host peer
		Comms_Device_SendPacket(commsDevice, &flash_write_acknowledge, sizeof(flash_write_acknowledge));
		// send the starting flash memory pointer to the host
		Comms_Device_SendPacket(commsDevice, &flash_app_write_address, sizeof(flash_app_write_address));
		memset(code_payload_packet, 0, sizeof(code_payload_packet));
		while (number_of_code_payloads > 0) {
			Comms_Device_RecvPacket(commsDevice, code_payload_packet, sizeof(code_payload_packet));
			flashWriteData (flashDevice, code_payload_packet, sizeof(code_payload_packet), flash_app_write_address);
			flash_app_write_address += CODE_PACKET_SIZE;
			memset(code_payload_packet, 0, CODE_PACKET_SIZE);
			// send the flash write acknowledge to host peer
			Comms_Device_SendPacket(commsDevice, &flash_write_acknowledge, sizeof(flash_write_acknowledge));
			// send the updated flash memory pointer to the host
			Comms_Device_SendPacket(commsDevice, &flash_app_write_address, sizeof(flash_app_write_address));
			number_of_code_payloads -= 1;
		}
		flash_write_status = FLASH_WRITE_OK;
		//send the flash write status to host peer
		Comms_Device_SendPacket(commsDevice, &flash_write_status, sizeof(flash_write_status));
		flash_app_write_address = (volatile uint8_t *)FLASH_APP_REGION_START;
	}
}

void bl_enable_read_write_protect (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

}

void run_application (uint32_t app_address) {
	turn_off_GREEN_LED_PORTB();
	lockFlashControlRegister (flashDevice);
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

