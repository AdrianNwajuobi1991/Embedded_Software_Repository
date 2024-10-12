/*
 * main.c
 *
 *  Created on: Apr 24, 2024
 *      Author: root
 */

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "comms_device.h"
#include "BootProtocolDefs.h"



typedef struct CommsDeviceOptions {
	int32_t baud_rate;
	char * deviceFile;
}CommsDeviceOptions;

static uint8_t * codePackage = NULL;

static comms_device_t commsDevice;

static void convert_file_to_array(char * filePath, uint8_t ** codePackage, unsigned long * fileSize);

static void setup_comms_device(comms_device_t * device, CommsDeviceOptions * options);

static unsigned long fileLength = 0;

static void exitHostBootloader (void);

static uint16_t preamble = 0x3F3F;

static void boot_loader_sequencer (char * argv[]);
static void boot_loader_setup(char * firmwareFilePathString,
		uint8_t ** codePackagePtr,
		unsigned long * fileSizeBytes,
		int32_t baudRate, char * deviceFile,
		CommsDeviceOptions * commsOpts);

static void run_boot_loader_logic (comms_device_t commsDevice, int operationType);

static void host_bl_get_version (comms_device_t commsDevice);
static void host_bl_get_help (comms_device_t commsDevice);
static void bl_get_chip_id (comms_device_t commsDevice);
static void bl_get_rdp_status (comms_device_t commsDevice);

static void (*boot_loader_operations[5]) (comms_device_t commsDevice) = {0, host_bl_get_version, host_bl_get_help,
		bl_get_chip_id, bl_get_rdp_status};


int main (int argc, char * argv[]) {
	printf("The bootloader client application is started.\n");
	boot_loader_sequencer(argv);
	return 0;
}

static void boot_loader_sequencer (char * argv[]) {
	char * firmWareFilePath = argv[1];
	char * deviceFilePath = argv[2];
	int32_t baudRate = atoi(argv[3]);
	int32_t operationType = atoi(argv[4]);
	CommsDeviceOptions commsOpts = {0};
	boot_loader_setup(firmWareFilePath, &codePackage, &fileLength, baudRate, deviceFilePath, &commsOpts);
	run_boot_loader_logic (commsDevice, operationType);
}

static void boot_loader_setup(char * firmwareFilePathString,
		uint8_t ** codePackagePtr,
		unsigned long * fileSizeBytes,
		int32_t baudRate, char * deviceFile,
		CommsDeviceOptions * commsOpts) {
	printf("boot loader client setup is beginning.\n");
	convert_file_to_array(firmwareFilePathString, codePackagePtr, fileSizeBytes);
	commsOpts->baud_rate = baudRate;
	commsOpts->deviceFile = deviceFile;
	setup_comms_device(&commsDevice, commsOpts);
	printf("boot loader client setup is completed.\n");
}


static void run_boot_loader_logic (comms_device_t commsDevice, int32_t operationType) {
	printf("main boot loader business logic starting.\n");
	boot_loader_operations[operationType] (commsDevice);

	exitHostBootloader();
}

static void bl_get_rdp_status (comms_device_t commsDevice) {
	uint8_t bl_get_rdp_status_pkt[6];
	uint8_t crcResponse[2];
	uint8_t ackPreambleResponse = 0;
	uint8_t mcu_flash_rdp_status = 0;
	bl_get_rdp_status_pkt[0] = 5;
	bl_get_rdp_status_pkt[1] = BL_GET_RDP_STATUS;
	uint32_t * crcPortionPtr = (uint32_t *)(bl_get_rdp_status_pkt+2);
	*crcPortionPtr = 0xABDE7C98;
	//send the preamble
	Comms_Device_SendPacket(commsDevice, &preamble, sizeof(preamble));
	//receive the ACK_PREAMBLE RESPONSE
	Comms_Device_RecvPacket(commsDevice, &ackPreambleResponse, sizeof(ackPreambleResponse));
	if (ackPreambleResponse == ACK_PREAMBLE) {
		printf("The ACK_PREAMBLE Response host_bl_get_rdp_status has been read here.\n");
		//send the length to follow: pkt[0]
		Comms_Device_SendPacket(commsDevice, bl_get_rdp_status_pkt, sizeof(bl_get_rdp_status_pkt[0]));
		//send the rest of pkt
		Comms_Device_SendPacket(commsDevice, bl_get_rdp_status_pkt+1, sizeof(bl_get_rdp_status_pkt)-1);
		//receive crcResponse pkt
		Comms_Device_RecvPacket(commsDevice, crcResponse, 2);
		printf("The CRC Response host_bl_get_rdp_status has been read here.\n");
		if (crcResponse[0] == ACK) {
			//receive the boot loader version value
			Comms_Device_RecvPacket(commsDevice, &mcu_flash_rdp_status, crcResponse[1]);
			if (mcu_flash_rdp_status == 0xAA) {
				printf("The MCU Flash Read Protection Status is %x: Level 0: No read protection.\n", mcu_flash_rdp_status);
			}
			if (mcu_flash_rdp_status == 0xCC) {
				printf("The MCU Flash Read Protection Status is %x: Level 2: chip protection.\n", mcu_flash_rdp_status);
			}
			if (mcu_flash_rdp_status != 0xCC && mcu_flash_rdp_status != 0xAA) {
				printf("The MCU Flash Read Protection Status is %x: Level 1: read protection of memories.\n", mcu_flash_rdp_status);
			}
		}
	}
}

static void bl_get_chip_id (comms_device_t commsDevice) {
	uint8_t bl_get_chip_id_pkt[6];
	uint8_t crcResponse[2];
	uint8_t ackPreambleResponse = 0;
	uint16_t MCU_CHIP_ID = 0xFFFF;
	bl_get_chip_id_pkt[0] = 5;
	bl_get_chip_id_pkt[1] = BL_GET_CID;
	uint32_t * crcPortionPtr = (uint32_t *)(bl_get_chip_id_pkt+2);
	*crcPortionPtr = 0xABDE7C98;
	//send the preamble
	Comms_Device_SendPacket(commsDevice, &preamble, sizeof(preamble));
	//receive the ACK_PREAMBLE RESPONSE
	Comms_Device_RecvPacket(commsDevice, &ackPreambleResponse, sizeof(ackPreambleResponse));
	if (ackPreambleResponse == ACK_PREAMBLE) {
		printf("The ACK_PREAMBLE Response host_bl_get_chip_id has been read here.\n");
		//send the length to follow: pkt[0]
		Comms_Device_SendPacket(commsDevice, bl_get_chip_id_pkt, sizeof(bl_get_chip_id_pkt[0]));
		//send the rest of pkt
		Comms_Device_SendPacket(commsDevice, bl_get_chip_id_pkt+1, sizeof(bl_get_chip_id_pkt)-1);
		//receive crcResponse pkt
		Comms_Device_RecvPacket(commsDevice, crcResponse, 2);
		printf("The CRC Response host_bl_get_chip_id has been read here.\n");
		if (crcResponse[0] == ACK) {
			//receive the boot loader version value
			Comms_Device_RecvPacket(commsDevice, &MCU_CHIP_ID, crcResponse[1]);
			printf("The MCU Chip ID is: %x\n", MCU_CHIP_ID);
		}
	}
}

static void host_bl_get_help (comms_device_t commsDevice) {
	uint8_t bl_get_version_pkt[6];
	uint8_t crcResponse[2];
	uint8_t ackPreambleResponse = 0;
	unsigned char  bootLoaderHelpMessage[50] = {0};
	bl_get_version_pkt[0] = 5;
	bl_get_version_pkt[1] = BL_GET_HELP;
	uint32_t * crcPortionPtr = (uint32_t *)(bl_get_version_pkt+2);
	*crcPortionPtr = 0xABDE7C98;
	//send the preamble
	Comms_Device_SendPacket(commsDevice, &preamble, sizeof(preamble));
	//receive the ACK_PREAMBLE RESPONSE
	Comms_Device_RecvPacket(commsDevice, &ackPreambleResponse, sizeof(ackPreambleResponse));
	if (ackPreambleResponse == ACK_PREAMBLE) {
		printf("The ACK_PREAMBLE Response host_bl_get_help has been read here.\n");
		//send the length to follow: pkt[0]
		Comms_Device_SendPacket(commsDevice, bl_get_version_pkt, sizeof(bl_get_version_pkt[0]));
		//send the rest of pkt
		Comms_Device_SendPacket(commsDevice, bl_get_version_pkt+1, sizeof(bl_get_version_pkt)-1);
		//receive crcResponse pkt
		Comms_Device_RecvPacket(commsDevice, crcResponse, 2);
		printf("The CRC Response host_bl_get_help has been read here.\n");
		if (crcResponse[0] == ACK) {
			//receive the boot loader version value
			Comms_Device_RecvPacket(commsDevice, bootLoaderHelpMessage, crcResponse[1]);
			printf("The MCU Boot Loader Help message is: %s\n", bootLoaderHelpMessage);
		}
	}
}

static void host_bl_get_version (comms_device_t commsDevice) {
	uint8_t bl_get_version_pkt[6];
	uint8_t crcResponse[2];
	uint8_t bootLoaderVersion = 0xFF;
	uint8_t ackPreambleResponse = 0;
	bl_get_version_pkt[0] = 5;
	bl_get_version_pkt[1] = BL_GET_VER;
	uint32_t * crcPortionPtr = (uint32_t *)(bl_get_version_pkt+2);
	*crcPortionPtr = 0xABDE7C98;
	//send the preamble
	Comms_Device_SendPacket(commsDevice, &preamble, sizeof(preamble));
	//receive the ACK_PREAMBLE RESPONSE
	Comms_Device_RecvPacket(commsDevice, &ackPreambleResponse, sizeof(ackPreambleResponse));
	if (ackPreambleResponse == ACK_PREAMBLE) {
		printf("The ACK_PREAMBLE Response host_bl_get_version has been read here.\n");
		//send the length to follow: pkt[0]
		Comms_Device_SendPacket(commsDevice, bl_get_version_pkt, sizeof(bl_get_version_pkt[0]));
		//send the rest of pkt
		Comms_Device_SendPacket(commsDevice, bl_get_version_pkt+1, sizeof(bl_get_version_pkt)-1);
		//receive crcResponse pkt
		Comms_Device_RecvPacket(commsDevice, crcResponse, 2);
		printf("The CRC Response host_bl_get_version has been read here.\n");
		if (crcResponse[0] == ACK) {
			//receive the boot loader version value
			Comms_Device_RecvPacket(commsDevice, &bootLoaderVersion, crcResponse[1]);
			printf("The MCU Boot Loader version is: %x\n", bootLoaderVersion);
		}
	}
}

static void exitHostBootloader (void)
{
	printf("main boot loader business logic completed.\n");
	printf("freeing the code package and exiting boot loader.\n");
	free(codePackage);
	Comms_Device_Disable(commsDevice);
	exit(EXIT_SUCCESS);
}


static void setup_comms_device(comms_device_t * device, CommsDeviceOptions * options) {
	*device = Comms_Init(INSTANCE_0, options);
}

static void convert_file_to_array(char * filePath, uint8_t ** codePackage, unsigned long * fileSize) {
	FILE *fileptr;
	unsigned long filelen;

	fileptr = fopen(filePath, "rb");  // Open the file in binary mode, Hard code path to ARM executable file for now
	if (fileptr == NULL) {
		printf("fileptr is null.\n");
		exit(EXIT_FAILURE);
	}
	printf("The firmware codefile is opened.\n");
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	*codePackage = (uint8_t *)malloc(filelen * sizeof(uint8_t)); // Enough memory for the file
	if (*codePackage == NULL) {
		printf("The code package array is null.\n");
		exit(EXIT_FAILURE);
	}
	fread(*codePackage, filelen, 1, fileptr); // Read in the entire file
	fclose(fileptr); // Close the file
	printf("The firmware codefile is loaded.\n");
	*fileSize = filelen;
}
