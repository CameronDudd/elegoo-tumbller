/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>

void initUsart(void);
bool uartAvailable(void);
unsigned char uartReceive(void);
void uartSendChar(char c);
void uartPrint(const char* str);
void uartPrintf(const char* format, ...);

#endif  // SERIAL_H
