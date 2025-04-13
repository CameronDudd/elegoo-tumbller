/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "led.h"

#ifdef UNIT_TEST
#include "mock_avr_delay.h"
#include "mock_avr_io.h"
#else
#include "avr/delay.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#endif

const Color COLOR_LED_OFF = {
    .r = HEX_LED_OFF,
    .g = HEX_LED_OFF,
    .b = HEX_LED_OFF,
};
const Color COLOR_LED_WHITE = {
    .r = HEX_LED_MAX,
    .g = HEX_LED_MAX,
    .b = HEX_LED_MAX,
};
const Color COLOR_LED_RED = {
    .r = HEX_LED_MAX,
    .g = HEX_LED_OFF,
    .b = HEX_LED_OFF,
};
const Color COLOR_LED_GREEN = {
    .r = HEX_LED_OFF,
    .g = HEX_LED_MAX,
    .b = HEX_LED_OFF,
};
const Color COLOR_LED_BLUE = {
    .r = HEX_LED_OFF,
    .g = HEX_LED_OFF,
    .b = HEX_LED_MAX,
};

void initLED() {
  // initialise data direction registers to zero (input)
  DDRB = 0;
  DDRD = 0;
  // initialise ports to zero
  PORTB = 0;
  PORTD = 0;

  DDRB |= (1 << PB5); // Set PB5 as output (for on board LED)
  DDRD |= (1 << PD3); // Set PD3 as output (for bit banging ws2812b module)
}

void toggleOnBoardLED() { PORTB ^= (1 << PB5); }

/* __ WS2812B Module __
 *
 * Pure bit banging
 *
 * Sequence Chart:
 *   0 Code: T0H T0L
 *   1 Code: T1H T1L
 * RET Code: Treset
 *
 * Data Transfer Time TH + TL = 1.25 us +/- 150ns
 * +-----+---------------------------+------------+-----------+-----------+
 * | T0H | 0 code, high voltage time | 0.35 us    |   5.6 clk | +/- 150ns |
 * | T1H | 1 code, high voltage time | 0.90 us    |  14.4 clk | +/- 150ns |
 * | T0L | 0 code, low voltage time  | 0.90 us    |  14.4 clk | +/- 150ns |
 * | T1L | 1 code, low voltage time  | 0.35 us    |   5.6 clk | +/- 150ns |
 * | RES | low voltage time          | Above 50us | 800.0 clk |           |
 * +-----+---------------------------+------------+----------+-----------+
 *
 * Composition of 24bit Data:
 * +-------------------------------------------------------------------------+
 * | G7 G6 G5 G4 G3 G2 G1 G0 R7 R6 R5 R4 R3 R2 R1 R0 B7 B6 B5 B4 B3 B2 B1 B0 |
 * +-------------------------------------------------------------------------+
 * NOTE (cameron): Follow the order of GRB to send data and the high bit sent
 * first
 *
 * To have the command cascaded to the other linked LEDs first 24bit will be
 * processed by D1 second by D2 third by D3 and so forth as long as they are
 * sent without the >=50us reset
 *
 * 1/16MHz  = 62.5 ns = 0.0625 us
 *
 */

#define TSMALL __asm__ __volatile__("nop\nnop\nnop\n")
#define TLARGE                                                                 \
  __asm__ __volatile__(                                                        \
      "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n")

static inline void _sendZero(void) __attribute__((always_inline));
static inline void _sendZero(void) {
  PORTD |= (1 << PD3);  // PULL HIGH
  TSMALL;               // T0H
  PORTD &= ~(1 << PD3); // PULL LOW
  TLARGE;               // TOL
}

static inline void _sendOne(void) __attribute__((always_inline));
static inline void _sendOne(void) {
  PORTD |= (1 << PD3);  // PULL HIGH
  TLARGE;               // T1H
  PORTD &= ~(1 << PD3); // PULL LOW
  TSMALL;               // T1L
}

static inline void _sendByte(uint8_t byte) __attribute__((always_inline));
static inline void _sendByte(uint8_t byte) {
  for (int i = 7; i >= 0; i--) {
    ((byte & (1 << i))) ? _sendOne() : _sendZero();
  }
}

void colorReset() {
  PORTD &= ~(1 << PD3);
  _delay_us(100);
}

void sendColor(Color color) {
  cli();
  _sendByte(color.g);
  _sendByte(color.r);
  _sendByte(color.b);
  sei();
}

void sendColors(const Color *colors, size_t numColors) {
  if (numColors == 0) {
    return;
  }
  const Color *end = colors + numColors;
  for (; colors < end; ++colors) {
    sendColor(*colors);
  }
  colorReset();
}
