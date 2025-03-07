/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define F_CPU 16000000UL  // 16 MHz
#define BAUD (unsigned int)9600
#define SCL_CLOCK 100000L  // 100kHz

// Asynchronous normal mode (U2Xn = 0)
#define UBRR_FROM_BAUD 103  // ( F_CPU / (16 * BAUD) ) - 1 = 103.16r error 0.2%

#endif  // CONSTANTS_H
