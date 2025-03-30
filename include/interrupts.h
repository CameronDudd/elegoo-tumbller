/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef INTERUPTS_H
#define INTERUPTS_H

extern volatile unsigned long millis;

void initEncoders();
void initTimers();
void sleepMs(unsigned long timeMs);

#endif  // INTERUPTS_H
