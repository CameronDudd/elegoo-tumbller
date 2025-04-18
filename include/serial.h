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
unsigned int serialAvailable();
unsigned char uartReceive();
void uartReceiveATResponse(char *buff, int buffSize);

#endif  // SERIAL_H
