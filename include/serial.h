/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef SERIAL_H
#define SERIAL_H

#include "ab1602.h"

extern volatile unsigned char *r;

void usartInit();
void usartEnableCapture();
void usartDisableCapture();
unsigned int serialAvailable();
unsigned char uartReceive();
ATStatusFlag uartReceiveATAttr(const char *attr, char *buff, int buffSize);
void uartReceiveATResponse(char *buff, int buffSize);
void uartPrint(const char *str);
void uartPrintf(const char *format, ...);

#endif  // SERIAL_H
