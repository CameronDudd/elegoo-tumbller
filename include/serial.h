/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef SERIAL_H
#define SERIAL_H

extern volatile unsigned char *r;

void usartInit();
void uartPrint(const char *str);
void uartPrintf(const char *format, ...);

#endif  // SERIAL_H
