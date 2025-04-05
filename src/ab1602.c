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

// TODO (cameron): uartRead imp

double BTSoftwareVersion() {
  uartPrint("AT+VERSION\r\n");
  uartRead();
  return 0.0;
}

const char *BTDeviceName() {
  // name, up to 18 bytes, default BT16
  uartPrint("AT+NAME\r\n");
  uartRead();
  return "";
}

void BTSetDeviceName(const char *name) {
  // name, up to 18 bytes, default BT16
  uartPrintf("AT+NAME=%s\r\n", name);
  uartRead();
}

long BTSerialBaudRate() {
  uartPrint("AT+BAUD?\r\n");
  uartRead();
  return 0;
}

void BTSetSerialBaudRate(BTBAUD baud) {
  uartPrintf("AT+BAUD=%l\r\n", baud);
  uartRead();
}

void BTReset() {
  uartPrint("AT+RESET\r\n");
  uartRead(); // OK\r\n
}

void BTTx() {} // TODO (cameron):

void BTRx() {} // TODO (cameron):
