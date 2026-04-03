/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#include <stdint.h>

extern volatile unsigned long leftWheelPulses;
extern volatile unsigned long rightWheelPulses;

void initMotors(void);
void initEncoders(void);
void enableMotors(void);
void disableMotors(void);
void setMotorsPercent(int8_t percent);
void setMotorStop(void);

#endif  // MOTOR_H
