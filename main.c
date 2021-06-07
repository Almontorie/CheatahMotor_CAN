
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "commands.h"

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


    // Send comands
    //zeroEncoder(socketCan, frame);
    sleep(1);
    enterMotorMode(socketCan, frame);
    torqueControl(socketCan, frame, 0x1234, 0x123, 0x123, 0x123, 0x123);
    sleep(5);
    exitMotorMode(socketCan, frame);


    if (close(socketCan) < 0)
    {
        perror("Close");
        return 1;
    }

    return 0;
}
