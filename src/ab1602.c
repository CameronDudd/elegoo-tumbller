/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "ab1602.h"
#include "serial.h"

// READ
// REQ: AT+<CMD>
// RES: +<CMD>=<PARAM>\r\n

// WRITE
// REQ: AT+<CMD><PARAM>\r\n
// RES: +<CMD>=<PARAM>\r\n OK\r\n

double BTSoftwareVersion() {
  uartPrint("AT+VERSION\r\n");
  return 0.0;
}

const char *BTDeviceName() {
  // name, up to 18 bytes, default BT16
  uartPrint("AT+NAME\r\n");
  return "";
}

void BTSetDeviceName(const char *name) {
  // name, up to 18 bytes, default BT16
  uartPrintf("AT+NAME=%s\r\n", name);
}

long BTSerialBaudRate() {
  uartPrint("AT+BAUD?\r\n");
  return 0;
}

void BTSetSerialBaudRate(BTBAUD baud) { uartPrintf("AT+BAUD=%l\r\n", baud); }

void BTReset() { uartPrint("AT+RESET\r\n"); }
