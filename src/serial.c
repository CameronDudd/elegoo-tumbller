/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#include "serial.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>
#include <util/delay.h>

#define UBRR_FROM_BAUD (uint16_t)103

// As outlined by the documentation
static void _uartTransmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) {  // wait until UDR0 ready to accept data
  }
  UDR0 = data;  // put data into the buffer
}

// As outlined by the documentation
void initUsart(void) {
  // reset
  UBRR0  = 0;
  UCSR0A = 0;
  UCSR0B = 0;
  UCSR0C = 0;

  // Set baud rate
  UBRR0L = (unsigned char)UBRR_FROM_BAUD;
  UBRR0H = (unsigned char)(UBRR_FROM_BAUD >> 8);

  // Enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // UCSZn2:0 bits select number of data bits in the frame
  // UPMn1:0 bits enable and set the type of parity bit
  // USBSn bit selects between one or two stop bits blank for 1 stop bit
  // Set frame format: 8data, 1stop bit -> set by bluetooth module
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8 bits, no parity, 1 stop bit
}

bool uartAvailable(void) { return (UCSR0A & (1 << RXC0)) ? true : false; }

unsigned char uartReceive(void) {
  while (!(UCSR0A & (1 << RXC0))) {
  }
  return UDR0;
}

void uartSendChar(char c) { _uartTransmit(c); }

void uartPrint(const char* str) {
  while (*str != '\0') {
    _uartTransmit(*str++);
  }
}

void uartPrintf(const char* format, ...) {
  char out[200];
  va_list args;
  va_start(args, format);
  vsprintf(out, format, args);
  va_end(args);
  uartPrint(out);
}
