
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

#define CONVERT_VEL(n) n+2047
#define CONVERT_POS(n) n+2047

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
    enterMotorMode(socketCan, frame);


    // rampCurrent(socketCan, frame);
    // rampVelocity(socketCan, frame);

    // Try Kd param
    int pos, vel, kp, kd, ff_current;
    pos = 0;
    vel = CONVERT_VEL(2048);
    kp = 0;
    kd = 0x100;
    ff_current = CONVERT_POS(0);
    torqueControl(socketCan, frame, pos, vel, kp, kd, ff_current);
    sleep(5);

    // Try Feed forward current param
    // torqueControl(socketCan, frame, 0, 0, 0, 0, 0);
    // sleep(5);
    // torqueControl(socketCan, frame, 0, 0, 0, 0, 0x7FF);
    // sleep(5);
    // torqueControl(socketCan, frame, 0, 0, 0, 0, 0xFFF);
    // sleep(5);

    exitMotorMode(socketCan, frame);


    if (close(socketCan) < 0)
    {
        perror("Close");
        return 1;
    }

    return 0;
}
