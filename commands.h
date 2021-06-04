
#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#include <linux/can.h>

#define CAN_ID 0x001
#define CAN_FRAMESIZE 8

// Motor control API
void enterMotorMode(int socketCan, struct can_frame frame);
void exitMotorMode(int socketCan, struct can_frame frame);
void zeroEncoder(int socketCan, struct can_frame frame);

void runMotor(int socketCan, struct can_frame frame);
void torqueControl(int socketCan, struct can_frame frame, uint16_t posiiton,
                    uint16_t velocity, uint16_t kp, uint16_t kd, uint16_t i);

#endif // COMMANDS_H
