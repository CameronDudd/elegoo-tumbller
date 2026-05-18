/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>
#include <stdint.h>

#include "command.h"

typedef enum {
  WAIT_START,
  READ_KEY,
  READ_VALUE,
} ParseStateT;

typedef struct {
  ParseStateT state;
  char key[KEY_SIZE];
  uint8_t keyIdx;
  char value[6];
  uint8_t valueIdx;
  CommandT type;
} SerialParser;

void initUsart(void);
bool uartAvailable(void);
bool uartReadByte(char* c);
void uartSendChar(char c);
void uartPrint(const char* str);
void uartPrintf(const char* format, ...);

char* rPtr;
void initSerialParser(SerialParser* p);
void readSerialBuff(SerialParser* p);

#endif  // SERIAL_H
