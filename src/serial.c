/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "serial.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/io.h>
#endif

#include <stdarg.h>
#include <stdio.h>

#include "constants.h"

/* As outlined by the documentation */
void usartInit() {
  UBRR0 = 0; // reset

  /* Set baud rate */
  UBRR0L = (unsigned char)UBRR_FROM_BAUD;
  UBRR0H = (unsigned char)(UBRR_FROM_BAUD >> 8);

  /* Enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);

  UBRR0 = UBRR_FROM_BAUD;
}

/* As outlined by the documentation */
static void _uartTransmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) { // wait until UDR0 ready to accept data
  }
  UDR0 = data; // put data into the buffer
}

void uartPrint(const char *str) {
  while (*str) {
    _uartTransmit(*str);
    str++;
  }
}

void uartPrintf(const char *format, ...) {
  char out[200];
  va_list args;
  va_start(args, format);
  vsprintf(out, format, args);
  va_end(args);
  uartPrint(out);
}
