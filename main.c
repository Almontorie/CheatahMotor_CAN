
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <byteswap.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>


#define CAN_ID 0x001
#define CAN_FRAMESIZE 8

#define CAN_ENTER_MOTORMODE  0xFFFFFFFFFFFFFFFC
#define CAN_EXIT_MOTORMODE   0xFFFFFFFFFFFFFFFD
#define CAN_ZERO_ENCODER     0xFFFFFFFFFFFFFFFC

int main(void)
{
	int socketCan;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

    printf("CAN Interface for CheetahMotor\n");

	if ((socketCan = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "can0" );
	ioctl(socketCan, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(socketCan, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
		perror("Bind");
		return 1;
	}

    // Enter motor mode
	frame.can_id = 0x001;
	frame.can_dlc = CAN_FRAMESIZE;
    uint64_t data = CAN_ENTER_MOTORMODE;
    data = bswap_64(data);
    memcpy(frame.data, &data, CAN_FRAMESIZE);

	if (write(socketCan, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		perror("Write");
		return 1;
	}

    // Run motor
	frame.can_id = 0x001;
	frame.can_dlc = CAN_FRAMESIZE;
    data = 0;
    data = bswap_64(data);
    memcpy(frame.data, &data, CAN_FRAMESIZE);

	if (write(socketCan, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		perror("Write");
		return 1;
	}

	if (close(socketCan) < 0)
    {
		perror("Close");
		return 1;
	}

	return 0;
}
