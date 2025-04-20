/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "ab1602.h"

#include <stddef.h>
#include <string.h>

#include "serial.h"

#ifdef UNIT_TEST
#include "mock_avr_delay.h"
#else
#include <util/delay.h>
#endif

#define RECV_SIZE (size_t)100
#define EXPECTED_VERSION "+VERSION=V1.0.0_001\r\n"

// READ
// REQ: AT+<CMD>
// RES: +<CMD>=<PARAM>\r\n

// WRITE
// REQ: AT+<CMD><PARAM>\r\n
// RES: +<CMD>=<PARAM>\r\n OK\r\n

// NOTE (cameron): Ensure at least 50ms have waited between any serial prints
// and AT commands

static char resvBuff[RECV_SIZE] = {'\0'};

static inline void _resetResvBuff() { memset(resvBuff, '\0', RECV_SIZE); }

void ATSoftwareVersionCheck() {
  /*
   * +================+=============================+
   * | Command        | Response                    |
   * +================+=============================+
   * | AT+VERSION\r\n | +VERSION<version>\r\nOK\r\n |
   * +================+=============================+
   */
  _resetResvBuff();
  _delay_ms(50);
  uartReceiveATAttr("VERSION", resvBuff, RECV_SIZE);
  uartPrintf("%s\r\n", resvBuff);
}

void ATDeviceNameCheck() {
  /*
   * +=============+==================+
   * | Command     | Response         |
   * +=============+==================+
   * | AT+NAME\r\n | +NAME=<name>\r\n |
   * +=============+==================+
   */
  _resetResvBuff();
  _delay_ms(50);
  // name, up to 18 bytes, default BT16
  uartReceiveATAttr("NAME", resvBuff, RECV_SIZE);
  uartPrintf("%s\r\n", resvBuff);
}

void ATSetDeviceName(const char *name) {
  /*
   * +===================+========================+
   * | Command           | Response               |
   * +===================+========================+
   * | AT+NAME<name>\r\n | +NAME=<name>\r\nOK\r\n |
   * +===================+========================+
   */
  _resetResvBuff();
  _delay_ms(50);
  // name, up to 19 bytes, default BT16
  uartPrintf("AT+NAME=%s\r\n", name);
  uartReceiveATResponse(resvBuff, RECV_SIZE);
  uartPrintf("%s", resvBuff);
}

void ATSerialBaudRateCheck() {
  /*
   * +==============+==================+
   * | Command      | Response         |
   * +==============+==================+
   * | AT+BAUD\r\n | +BAUD=<baud>\r\n |
   * +==============+==================+
   */
  _resetResvBuff();
  _delay_ms(50);
  uartReceiveATAttr("BAUD", resvBuff, RECV_SIZE);
  uartPrintf("%s\r\n", resvBuff);
}

void ATSetSerialBaudRate(BTBaud baud) {
  /*
   * +====================+========================+
   * | Command            | Response               |
   * +====================+========================+
   * | AT+BAUD=<baud>\r\n | +BAUD=<baud>\r\nOK\r\n |
   * +====================+========================+
   */
  _resetResvBuff();
  _delay_ms(50);
  uartPrintf("AT+BAUD=%i\r\n", baud);
  uartReceiveATResponse(resvBuff, RECV_SIZE);
  uartPrintf("%s", resvBuff);
}

void ATReset() {
  /*
   * +==============+==========+
   * | Command      | Response |
   * +==============+==========+
   * | AT+RESET\r\n | OK\r\n   |
   * +==============+==========+
   */
  _resetResvBuff();
  _delay_ms(50);
  uartPrint("AT+RESET\r\n");
  uartReceiveATResponse(resvBuff, RECV_SIZE);
  uartPrintf("%s", resvBuff);
}
