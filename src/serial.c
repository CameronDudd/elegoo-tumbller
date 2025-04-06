/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "serial.h"
#include "constants.h"
#include "timer.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#include <avr/io.h>
#endif

#include <stdarg.h>
#include <stdio.h>

#define RX_BUFF_SIZE 15
volatile unsigned char commandBuff[RX_BUFF_SIZE] = {'\0'};
volatile unsigned char *r = commandBuff; // reading from the command buffer
volatile unsigned char *p = commandBuff; // writing to the command buffer

// As outlined by the documentation
void usartInit() {
  // reset
  UBRR0 = 0;
  UCSR0B = 0;
  UCSR0C = 0;

  // Set baud rate
  UBRR0L = (unsigned char)UBRR_FROM_BAUD;
  UBRR0H = (unsigned char)(UBRR_FROM_BAUD >> 8);

  // Enable receiver and transmitter and receiver interrupt
  UCSR0B = (1 << RXEN0) | (1 << TXEN0); //  | (1 << RXCIE0);

  // UCSZn2:0 bits select number of data bits in the frame
  // UPMn1:0 bits enable and set the type of parity bit
  // USBSn bit selects between one or two stop bits blank for 1 stop bit
  // Set frame format: 8data, 1stop bit -> set by bluetooth module
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits, no parity, 1 stop bit

  UBRR0 = UBRR_FROM_BAUD;
}

// As outlined by the documentation
static void _uartTransmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) { // wait until UDR0 ready to accept data
  }
  UDR0 = data; // put data into the buffer
}

unsigned char _uartReceive() {
  while (!(UCSR0A & (1 << RXC0))) {
  }
  return UDR0;
}

// void uartReceive() {
//   uartPrintf("Got %c\r\n", _uartReceive());
//   uartPrintf("test\r\n");
// for (size_t n = 0; n < buffSize - 1; n++) {
//   char c = _uartReceive();
//   uartPrintf("%c\r\n", c);
//   buff[n] = c;
// }
// buff[buffSize - 1] = '\0';
// }

void uartPrint(const char *str) {
  while (*str != '\0') {
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

ISR(USART_RX_vect) {
  cli(); // disable interrupts
  if ((p - commandBuff) >= RX_BUFF_SIZE - 1) {
    p = commandBuff; // round robin
  }
  *p++ = UDR0;
  sei(); // enable interrupts
}
