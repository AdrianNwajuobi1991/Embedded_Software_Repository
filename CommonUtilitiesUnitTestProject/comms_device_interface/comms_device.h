/*
 * comms_device.h
 *
 *  Created on: Jul 31, 2024
 *      Author: root
 */

#ifndef COMMS_DEVICE_H_
#define COMMS_DEVICE_H_

#include <stdint.h>

enum {
	INSTANCE_0
};

typedef struct CommsDeviceType * comms_device_t;

comms_device_t Comms_Init(int instance, void * args);

void Comms_Device_Enable (comms_device_t comms_device);

void Comms_Device_Disable (comms_device_t comms_device);

void Comms_Device_SendPacket(comms_device_t comms_device, void * data, uint32_t numBytes);

void Comms_Device_RecvPacket(comms_device_t comms_device, void * recvPacketBuffer, uint32_t numBytes);

#endif /* COMMS_DEVICE_H_ */
