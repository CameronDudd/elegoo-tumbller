/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef INTERUPTS_H
#define INTERUPTS_H

extern volatile unsigned long millis;
extern volatile unsigned long leftWheelPulses;
extern volatile unsigned long rightWheelPulses;

void initEncoders();

#endif  // INTERUPTS_H
