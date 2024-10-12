/*
 * boot_loader_protocol_suite.c
 *
 *  Created on: Aug 22, 2024
 *      Author: root
 */
#include "boot_loader_protocol_suite.h"
#include "stm32f7xx.h"

#define BOOT_LOADER_VERSION		0x82

static bool is_crc_valid (uint8_t * command_packet, uint32_t length, uint32_t crc_expected);
static void send_ack_sequence(comms_device_t commsDevice, uint8_t length_next_packet);

void bl_get_version (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {
	uint8_t boot_loader_version = BOOT_LOADER_VERSION;
	uint32_t nonCRCPacketPortionLength = length-sizeof(uint32_t);
	uint32_t crc_expected = *(uint32_t *)(command_packet+nonCRCPacketPortionLength);
	if (is_crc_valid(command_packet, nonCRCPacketPortionLength, crc_expected) == true) {
		send_ack_sequence(commsDevice, 1);
		//send the boot loader version to host peer
		Comms_Device_SendPacket(commsDevice, &boot_loader_version, 1);
	}
}

void bl_get_help (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {
	unsigned char help_message[]="Supported command IDs range from 1-8.";
	uint32_t nonCRCPacketPortionLength = length-sizeof(uint32_t);
	uint32_t crc_expected = *(uint32_t *)(command_packet+nonCRCPacketPortionLength);
	if (is_crc_valid(command_packet, nonCRCPacketPortionLength, crc_expected) == true) {
		send_ack_sequence(commsDevice, (sizeof(help_message)/sizeof(help_message[0])));
		//send the help message response to host peer
		Comms_Device_SendPacket(commsDevice, help_message, (sizeof(help_message)/sizeof(help_message[0])));
	}
}

void bl_get_chip_id (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {
	uint16_t chip_id;
	chip_id = (uint16_t) DBGMCU->IDCODE & 0x0FFF;
	uint32_t nonCRCPacketPortionLength = length-sizeof(uint32_t);
	uint32_t crc_expected = *(uint32_t *)(command_packet+nonCRCPacketPortionLength);
	if (is_crc_valid(command_packet, nonCRCPacketPortionLength, crc_expected) == true) {
		send_ack_sequence(commsDevice, sizeof(uint16_t));
		//send the chip id response to host peer
		Comms_Device_SendPacket(commsDevice, &chip_id, sizeof(uint16_t));
	}
}

void bl_get_rdp_status (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

	uint8_t read_protection_status;
	read_protection_status = (uint8_t)((*(volatile uint32_t *)0x1FFF0000) >> 8);
	uint32_t nonCRCPacketPortionLength = length-sizeof(uint32_t);
	uint32_t crc_expected = *(uint32_t *)(command_packet+nonCRCPacketPortionLength);
	if (is_crc_valid(command_packet, nonCRCPacketPortionLength, crc_expected) == true) {
		send_ack_sequence(commsDevice, sizeof(uint8_t));
		//send the flash read protection status to host peer
		Comms_Device_SendPacket(commsDevice, &read_protection_status, sizeof(uint8_t));
	}
}

void bl_go_to_addr (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

}

void bl_flash_erase (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

}

void bl_mem_write (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

}

void bl_enable_read_write_protect (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length) {

}

static void send_ack_sequence(comms_device_t commsDevice, uint8_t length_next_packet) {
	uint8_t crcResponse[2];
	crcResponse[0] = ACK;
	crcResponse[1] = length_next_packet;
	//send the ACK response and length of the data to follow
	Comms_Device_SendPacket(commsDevice, crcResponse, 2);
}

static bool is_crc_valid (uint8_t * command_packet, uint32_t length, uint32_t crc_expected) {
	return (crc_expected == 0xABDE7C98);
	//return true;
}

