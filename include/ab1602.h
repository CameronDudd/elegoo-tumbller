/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef AB1602_H
#define AB1602_H

typedef enum {
  // Default: 0 (9600)
  BAUD_9600   = 1,
  BAUD_19200  = 2,
  BAUD_38400  = 3,
  BAUD_54600  = 4,
  BAUD_115200 = 5,
} BTBaud;

typedef enum {
  STATUS_NULL     = 0b00000000,  // 0
  STATUS_OK       = 0b00000001,  // 1
  STATUS_ERROR    = 0b00000010,  // 2
  STATUS_TIMEOUT  = 0b00000100,  // 4
  STATUS_OVERFLOW = 0b00001000,  // 8
} ATStatusFlag;

void ATSoftwareVersionCheck();
void ATDeviceNameCheck();
void ATSetDeviceName(const char *name);
void ATSerialBaudRateCheck();
void ATSetSerialBaudRate(BTBaud baud);
void ATReset();

#endif  // AB1602_H
