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

// TODO (cameron): handle receive

void BTSoftwareVersion() { uartPrint("AT+VERSION\r\n"); }

void BTDeviceName() {
  // name, up to 18 bytes, default BT16
  uartPrint("AT+NAME\r\n");
}

void BTSetDeviceName(const char *name) {
  // name, up to 19 bytes, default BT16
  uartPrintf("AT+NAME=%s\r\n", name);
}

void BTSerialBaudRate() { uartPrint("AT+BAUD?\r\n"); }

void BTSetSerialBaudRate(BTBaud baud) { uartPrintf("AT+BAUD=%i\r\n", baud); }

void BTReset() { uartPrint("AT+RESET\r\n"); }
