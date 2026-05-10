/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#include <stdint.h>

extern volatile int32_t leftWheelPulses;
extern volatile int32_t rightWheelPulses;

void initMotors(void);
void initEncoders(void);
void resetEncoders(void);
void enableMotors(void);
void disableMotors(void);
void setMotorsPercent(int8_t percent);
void setMotorStop(void);
int32_t getLeftWheelPulses(void);
int32_t getRightWheelPulses(void);

#endif  // MOTOR_H
