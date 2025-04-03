/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/io.h>
#endif

#define L_MOTOR_ROTATION_DIRECTION PB4
#define R_MOTOR_ROTATION_DIRECTION PD7

void initPWM();
void initMotors();
void enableMotors();
void disableMotors();
void setSpeed(uint8_t speed);
void forward();
void reverse();
void stop();

#endif  // MOTOR_H
