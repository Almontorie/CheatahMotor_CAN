
#include "commands.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <byteswap.h>

#define CAN_ENTER_MOTORMODE  0xFFFFFFFFFFFFFFFC
#define CAN_EXIT_MOTORMODE   0xFFFFFFFFFFFFFFFD
#define CAN_ZERO_ENCODER     0xFFFFFFFFFFFFFFFE

// Enter motor mode
void enterMotorMode(int socketCan, struct can_frame frame)
{
	frame.can_id = 0x001;
	frame.can_dlc = CAN_FRAMESIZE;
    uint64_t data = CAN_ENTER_MOTORMODE;
    data = bswap_64(data);
    memcpy(frame.data, &data, CAN_FRAMESIZE);

	if (write(socketCan, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
		perror("Write");
	}
}

// Exit motor mode
void exitMotorMode(int socketCan, struct can_frame frame)
{
	frame.can_id = 0x001;
	frame.can_dlc = CAN_FRAMESIZE;
    uint64_t data = CAN_EXIT_MOTORMODE;
    data = bswap_64(data);
    memcpy(frame.data, &data, CAN_FRAMESIZE);

	if (write(socketCan, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
		perror("Write");
	}
}

// Set zero encoder
void zeroEncoder(int socketCan, struct can_frame frame)
{
	frame.can_id = 0x001;
	frame.can_dlc = CAN_FRAMESIZE;
    uint64_t data = CAN_ZERO_ENCODER;
    data = bswap_64(data);
    memcpy(frame.data, &data, CAN_FRAMESIZE);

	if (write(socketCan, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
		perror("Write");
	}
}

// Run motor
void runMotor(int socketCan, struct can_frame frame)
{
	frame.can_id = 0x001;
	frame.can_dlc = CAN_FRAMESIZE;
    uint64_t data = 0;
    data = bswap_64(data);
    memcpy(frame.data, &data, CAN_FRAMESIZE);

	if (write(socketCan, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
		perror("Write");
	}
}
