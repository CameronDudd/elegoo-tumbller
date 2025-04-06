/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef AB1602_H
#define AB1602_H

typedef enum {
  // Default: 0 (9600)
  BAUD_9600 = 1,
  BAUD_19200 = 2,
  BAUD_38400 = 3,
  BAUD_54600 = 4,
  BAUD_115200 = 5,
} BTBaud;

void BTSoftwareVersion();
void BTDeviceName();
void BTSetDeviceName(const char *name);
void BTSerialBaudRate();
void BTSetSerialBaudRate(BTBaud baud);
void BTReset();

#endif  // AB1602_H
