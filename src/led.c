/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "led.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/io.h>
#endif

void initLED() {
  DDRB |= (1 << PB5);  // Set PB5 as output (for LED)
  DDRD = 0x00;         // Set all D port pins to input
}

void toggleLED() { PORTB ^= (1 << PB5); }
