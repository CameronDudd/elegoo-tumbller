/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "serial.h"

#include <stdarg.h>
#include <stdio.h>

#include "constants.h"
#include "timer.h"

#ifdef UNIT_TEST
#include "mock_avr_delay.h"
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#endif

#define RX_BUFF_SIZE 500
volatile unsigned char uartRxBuff[RX_BUFF_SIZE] = {'\0'};
volatile unsigned char *r                       = uartRxBuff;  // reading from the command buffer
volatile unsigned char *p                       = uartRxBuff;  // writing to the command buffer

// As outlined by the documentation
void usartInit() {
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

  UBRR0 = UBRR_FROM_BAUD;
}

void usartEnableCapture() { UCSR0B |= (1 << RXCIE0); }

void usartDisableCapture() { UCSR0B &= ~(1 << RXCIE0); }

// As outlined by the documentation
static void _uartTransmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) {  // wait until UDR0 ready to accept data
  }
  UDR0 = data;  // put data into the buffer
}

unsigned int serialAvailable() { return (UCSR0A & (1 << RXC0)) ? 1 : 0; }

unsigned char uartReceive() {
  while (!(UCSR0A & (1 << RXC0))) {
  }
  return UDR0;
}

ATStatusFlag uartReceiveATAttr(const char *attr, char *buff, int buffSize) {
  cli();
  unsigned long startTs = millis;
  sei();
  ATStatusFlag s = STATUS_NULL;
  char c;
  char *current = buff;
  uartPrintf("AT+%s\r\n", attr);
  while (s == STATUS_NULL) {
    if ((millis - startTs) > 3000) {
      s |= STATUS_TIMEOUT;
    }
    if ((current - buff) > (buffSize - 1)) {
      s |= STATUS_OVERFLOW;
    }
    if (UCSR0A & (1 << RXC0)) {  // Character received
      c          = UDR0;         // Read character
      *current++ = c;            // Put character into buffer
      if (c == '\n') {           // Stop signal
        s |= STATUS_OK;
      }
    }
  }
  *current = '\0';  // Null terminated
  return s;
}

void uartReceiveATResponse(char *buff, int buffSize) {
  // Response will be original command without the AT prefix
  cli();
  unsigned long startTs = millis;
  sei();
  char *current = buff;
  while (((millis - startTs) < 1000) &&       // Timeout
         ((current - buff) < (buffSize - 1))  // Overflow
  ) {                                         // TODO (cameron): Check for termination bytes ie \r\n, \r\nOK\r\n etc
    if (UCSR0A & (1 << RXC0)) {               // Character received
      *current++ = UDR0;                      // Read character
    }
  }
  *current = '\0';  // Null terminated
}

void uartPrint(const char *str) {
  while (*str != '\0') {
    _uartTransmit(*str++);
  }
  _delay_ms(10);  // Add a small delay after sending data
}

void uartPrintf(const char *format, ...) {
  char out[200];
  va_list args;
  va_start(args, format);
  vsprintf(out, format, args);
  va_end(args);
  uartPrint(out);
}

void getCommand() {
  char buff[100] = {'\0'};
  char *b        = buff;
  while ((r < p) && (*r != '\0')) {
    *b++ = *r++;
  }
  *b++ = '\0';
}

ISR(USART_RX_vect) {  // if interrupt is enabled write into the buffer
  cli();              // disable interrupts
  if ((p - uartRxBuff) >= RX_BUFF_SIZE - 1) {
    p = uartRxBuff;  // round robin
  }
  *p++ = UDR0;
  sei();  // enable interrupts
}
