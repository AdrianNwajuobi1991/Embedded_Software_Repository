#include "comms_device.h"
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "protocol_endian_utils.h"


#define DEVICE_INIT_FAILURE		-1
#define DEVICE_INIT_SUCCESS		1

/*
 * structure to hold configuration aspects of the tty USB RF radio.
 */

typedef struct CommsDeviceType {
	int instanceID;
	/*
	 * struct for serial port configurations
	 */
	struct termios ttyUSB;
	/*
	 * file descriptor for the device.
	 * In Linux, everything is a file.
	 */
	int file_desc;
	/*
	 * the file path of the device in the devfs
	 */
	char * device_path;
	/*
	 * the speed of the bit-rate to send and receive data
	 */
	int32_t baud_rate;
}CommsDeviceType ;

typedef struct CommsDeviceOptions {
	int32_t baud_rate;
	char * deviceFile;
}CommsDeviceOptions;

static CommsDeviceType rf_devices[1];

static void setCommsTrancieverSpeed(comms_device_t device);
static void ttyUSBConfigure(comms_device_t device);
static void Comms_Device_Configure(comms_device_t comms_device, void * args);


comms_device_t Comms_Init(int instance, void * args) {
	protocol_endian_utils_setup();
	rf_devices[instance].instanceID = instance;
	comms_device_t device = &rf_devices[instance];
	Comms_Device_Configure(device, args);
	return device;
}

static void Comms_Device_Configure(comms_device_t comms_device, void * args) {
	CommsDeviceOptions * commsDeviceOptions = (CommsDeviceOptions *)args;
	comms_device->device_path = commsDeviceOptions->deviceFile;
	comms_device->file_desc = open(comms_device->device_path , O_RDWR);
	comms_device->baud_rate = commsDeviceOptions->baud_rate;
	if(comms_device->file_desc < 0) {
		printf("comms device init failure. Exiting now.\n");
		exit(DEVICE_INIT_FAILURE);
	}else{
		//tcflush(comms_device->file_desc, TCIOFLUSH);
		ttyUSBConfigure(comms_device);
		printf("%s\n",comms_device->device_path);
	}
}

static void ttyUSBConfigure(comms_device_t device) {
	/* initialize the struct termios for the serial port. It is a structure used as an interface to control asynchronous
	 * communication ports. */
	if(tcgetattr(device->file_desc, &(device->ttyUSB)) != 0) {
		printf("tcgetattr failure. Exiting now.\n");
		exit(DEVICE_INIT_FAILURE);
	}
	device->ttyUSB.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	device->ttyUSB.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	device->ttyUSB.c_cflag &= ~CSIZE; // Clear all the size bits, then use 8 data bits
	device->ttyUSB.c_cflag |= CS8; // 8 bits per byte (most common)
	device->ttyUSB.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	device->ttyUSB.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	device->ttyUSB.c_lflag &= ~ICANON;
	device->ttyUSB.c_lflag &= ~ECHO; // Disable echo
	device->ttyUSB.c_lflag &= ~ECHOE; // Disable erasure
	device->ttyUSB.c_lflag &= ~ECHONL; // Disable new-line echo
	device->ttyUSB.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	device->ttyUSB.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	device->ttyUSB.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
	device->ttyUSB.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	device->ttyUSB.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	device->ttyUSB.c_cc[VTIME] = 220;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	device->ttyUSB.c_cc[VMIN] = 0;
	setCommsTrancieverSpeed(device);
}

static void setCommsTrancieverSpeed(comms_device_t device) {
	switch(device->baud_rate) {
	case 9600:
		cfsetispeed(&(device->ttyUSB), B9600);
		cfsetospeed(&(device->ttyUSB), B9600);
		break;
	case 19200:
		cfsetispeed(&(device->ttyUSB), B19200);
		cfsetospeed(&(device->ttyUSB), B19200);
		break;
	case 38400:
		cfsetispeed(&(device->ttyUSB), B38400);
		cfsetospeed(&(device->ttyUSB), B38400);
		break;
	case 115200:
		cfsetispeed(&(device->ttyUSB), B115200);
		cfsetospeed(&(device->ttyUSB), B115200);
		break;
	default:
		cfsetispeed(&(device->ttyUSB), B115200);
		cfsetospeed(&(device->ttyUSB), B115200);
	}
	// Save tty settings, also checking for error
	if (tcsetattr(device->file_desc, TCSANOW, &(device->ttyUSB)) != 0) {
		printf("tcgetattr failure. Exiting now.\n");
		exit(DEVICE_INIT_FAILURE);
	}
}

void Comms_Device_SendPacket(comms_device_t comms_device, void * data, uint32_t numBytes) {
	hostToProtocolEndiannessConvert(data, numBytes);
	write(comms_device->file_desc, data, numBytes);
	hostToProtocolEndiannessConvert(data, numBytes);
}

void Comms_Device_RecvPacket(comms_device_t comms_device, void * recvPacketBuffer, uint32_t numBytes) {
	/*
	uint32_t bytesRead = 0;
	bytesRead = read(comms_device->file_desc, recvPacketBuffer+bytesRead, numBytes-bytesRead);
	while (bytesRead < numBytes) {
		printf("read only %d bytes, need %d more bytes for complete read: \n", bytesRead, (numBytes-bytesRead));
		bytesRead += read(comms_device->file_desc, recvPacketBuffer+bytesRead, numBytes-bytesRead);
	}
	protocolToHostEndiannessConvert(recvPacketBuffer, numBytes);
	*/
	read(comms_device->file_desc, recvPacketBuffer, numBytes);
	protocolToHostEndiannessConvert(recvPacketBuffer, numBytes);
}

void Comms_Device_Disable(comms_device_t comms_device) {
	protocol_endian_utils_teardown();
	close(comms_device->file_desc);
}

