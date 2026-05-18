/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#include "serial.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "command.h"

#define RECV_BUFF_SIZE 255
#define UBRR_FROM_BAUD (uint16_t)103

static char recvBuff[RECV_BUFF_SIZE] = {'\0'};
char* rPtr                           = recvBuff;
static char* wPtr                    = recvBuff;
static const char* recvBuffEnd       = recvBuff + RECV_BUFF_SIZE;

// As outlined by the documentation
static void uartTransmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) {  // wait until UDR0 ready to accept data
  }
  UDR0 = data;  // put data into the buffer
}

static inline void resetParser(SerialParser* p) {
  p->state    = WAIT_START;
  p->keyIdx   = 0;
  p->valueIdx = 0;
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

  // Enable receiver, transmitter, receiver interrupt
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

  // UCSZn2:0 bits select number of data bits in the frame
  // UPMn1:0 bits enable and set the type of parity bit
  // USBSn bit selects between one or two stop bits blank for 1 stop bit
  // Set frame format: 8data, 1stop bit -> set by bluetooth module
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8 bits, no parity, 1 stop bit
}

bool uartAvailable(void) { return (rPtr == wPtr) ? false : true; }

bool uartReadByte(char* c) {
  if (uartAvailable()) {
    *c = *rPtr++;
    if (rPtr >= recvBuffEnd) {
      rPtr = recvBuff;
    }
    return true;
  }
  return false;
}

// unsigned char uartReceive(void) {
//   while (!(UCSR0A & (1 << RXC0))) {
//   }
//   return UDR0;
// }

void uartSendChar(char c) { uartTransmit(c); }

void uartPrint(const char* str) {
  while (*str != '\0') {
    uartTransmit(*str++);
  }
}

void uartPrintf(const char* format, ...) {
  char out[200];
  va_list args;
  va_start(args, format);
  vsnprintf(out, sizeof(out), format, args);
  va_end(args);
  uartPrint(out);
}

void initSerialParser(SerialParser* p) {
  p->state    = WAIT_START;
  *p->key     = '\0';
  p->keyIdx   = 0;
  *p->value   = '\0';
  p->valueIdx = 0;
  p->type     = NUL;
}

void readSerialBuff(SerialParser* p) {
  //  READ: =abcd;
  // WRITE: +abcd=1234.1234;
  char c;
  while (uartReadByte(&c)) {
    switch (p->state) {
      case WAIT_START:   // Waiting for command start
        if (c == '=') {  // READ
          p->state    = READ_KEY;
          p->keyIdx   = 0;
          p->valueIdx = 0;
          p->type     = GET;
        } else if (c == '+') {  // WRITE
          p->state    = READ_KEY;
          p->keyIdx   = 0;
          p->valueIdx = 0;
          p->type     = SET;
        }
        break;

      case READ_KEY:
        if (c == '=') {
          p->key[p->keyIdx] = '\0';
          if (p->type == SET) {  // Done reading key next read value
            p->state = READ_VALUE;
          }
        } else if (c == ';') {  // Done reading key push get command to queue
          Command cmd;
          cmd.type = GET;
          memcpy(cmd.key, p->key, p->keyIdx + 1);
          cmd.key[p->keyIdx] = '\0';
          cmd.value          = 0.0f;
          pushCmd(&cmd);
          resetParser(p);
        } else {
          if (p->keyIdx < KEY_SIZE - 1) {
            p->key[p->keyIdx++] = c;
          }
        }
        break;

      case READ_VALUE:
        if (c == ';') {
          Command cmd;
          cmd.type = SET;
          memcpy(cmd.key, p->key, p->keyIdx + 1);
          cmd.key[p->keyIdx]    = '\0';
          p->value[p->valueIdx] = '\0';
          cmd.value             = atof(p->value);
          pushCmd(&cmd);
          resetParser(p);
        } else {
          if (p->valueIdx < KEY_SIZE - 1) {
            p->value[p->valueIdx++] = c;
          }
        }
        break;
    }
  }
}

ISR(USART_RX_vect) {
  char* n = wPtr + 1;
  if (n >= recvBuffEnd) {
    n = recvBuff;
  }
  *wPtr = UDR0;
  wPtr  = n;
  if (wPtr == rPtr) {
    if (++rPtr >= recvBuffEnd) {
      rPtr = recvBuff;
    }
  }
}
