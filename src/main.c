/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include <avr/interrupt.h>

#include "serial.h"

void init() {
  uartPrint("Usart init\r\n");
  usartInit();
  uartPrint("Usart init done\r\n");
}

int main() {
  uartPrint("Init\r\n");
  init();
  uartPrint("Init done\r\n");
  uartPrint("Hello, world!\r\n");
}
