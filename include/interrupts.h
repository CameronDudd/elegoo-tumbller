/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef INTERUPTS_H
#define INTERUPTS_H

extern volatile unsigned long long millis;

void initEncoders();
void initTimers();

#endif  // INTERUPTS_H
