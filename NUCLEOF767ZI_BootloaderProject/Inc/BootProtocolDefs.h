#ifndef	_BOOT_PROTOCOL_DEFS_H
#define	_BOOT_PROTOCOL_DEFS_H

#define ACK_PREAMBLE			0x24
#define ACK						0x25
#define NACK					0x26
#define FLASH_WRITE_NOT_DONE	0x27
#define FLASH_WRITE_DONE		0x28
#define CODE_PACKET_SIZE		128

#define BL_GET_VER			1
#define BL_GET_HELP			2
#define BL_GET_CID			3
#define BL_GET_RDP_STATUS	4
#define BL_GO_TO_ADDR		5
#define BL_FLASH_ERASE		6
#define BL_FLASH_WRITE		7
#define BL_EN_R_W_PROTECT	8

#endif
