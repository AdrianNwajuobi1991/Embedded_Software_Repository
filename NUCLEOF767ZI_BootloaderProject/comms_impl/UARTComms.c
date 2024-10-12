#include "comms_device.h"
#include "USART_Driver.h"
#include "protocol_endian_utils.h"
#include <stdbool.h>


#define NUM_DEVICES 2

typedef struct CommsDeviceType {
	int instanceID;
	usart_device ud;
}CommsDeviceType;

static CommsDeviceType comms_devices[NUM_DEVICES];

comms_device_t Comms_Init(int instance, void * args) {
	protocol_endian_utils_setup();
	usart_device usartDevice = (usart_device)args;
	comms_devices[instance].instanceID = instance;
	comms_devices[instance].ud = usartDevice;
	return &comms_devices[instance];
}

void Comms_Device_Enable (comms_device_t comms_device) {
	enableUSARTDevice(comms_device->ud);
}

void Comms_Device_Disable (comms_device_t comms_device) {
	disableUSARTDevice (comms_device->ud, false);
}

void Comms_Device_SendPacket(comms_device_t comms_device, void * data, uint32_t numBytes) {
	hostToProtocolEndiannessConvert(data, numBytes);
	transmit_packet (comms_device->ud, (uint8_t *)data, numBytes);
}

void Comms_Device_RecvPacket(comms_device_t comms_device, void * recvPacketBuffer, uint32_t numBytes) {
	recieve_packet (comms_device->ud, (uint8_t *)recvPacketBuffer, numBytes);
	protocolToHostEndiannessConvert(recvPacketBuffer, numBytes);
}

void Comms_Finalize(comms_device_t comms_device) {
	protocol_endian_utils_teardown();
}
