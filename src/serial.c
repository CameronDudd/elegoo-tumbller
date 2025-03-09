/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "serial.h"

#include <avr/io.h>  // memory address definitions
#include <stdarg.h>
#include <stdio.h>

#include "constants.h"

/* As outlined by the documentation */
void usart_init() {
  UBRR0 = 0;  // reset

  /* Set baud rate */
  UBRR0H = (unsigned char)(UBRR_FROM_BAUD >> 8);
  UBRR0L = (unsigned char)UBRR_FROM_BAUD;

  /* Enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);

  UBRR0 = UBRR_FROM_BAUD;
}

/* As outlined by the documentation */
static void _uart_transmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) {  // wait until UDR0 ready to accept data
  }
  UDR0 = data;  // put data into the buffer
}

void uart_print(const char* str) {
  while (*str) {
    _uart_transmit(*str);
    str++;
  }
}

void uart_printf(const char* format, ...) {
  char out[200];
  va_list args;
  va_start(args, format);
  vsprintf(out, format, args);
  va_end(args);
  uart_print(out);
}
