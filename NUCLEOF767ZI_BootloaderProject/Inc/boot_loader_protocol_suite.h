/*
 * boot_loader_protocol_suite.h
 *
 *  Created on: Aug 22, 2024
 *      Author: root
 */

#ifndef BOOT_LOADER_PROTOCOL_SUITE_H_
#define BOOT_LOADER_PROTOCOL_SUITE_H_

#include <stdint.h>
#include <stdbool.h>
#include "comms_device.h"
#include "BootProtocolDefs.h"

void bl_get_version (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);
void bl_get_help (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);
void bl_get_chip_id (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);
void bl_get_rdp_status (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);
void bl_go_to_app_address (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);
void bl_flash_erase (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);
void bl_mem_write (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);
void bl_enable_read_write_protect (uint8_t * command_packet, comms_device_t commsDevice, uint32_t length);

void run_application (uint32_t app_address);

#endif /* BOOT_LOADER_PROTOCOL_SUITE_H_ */
