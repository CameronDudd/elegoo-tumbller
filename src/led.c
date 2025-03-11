/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "led.h"

void initLED() {
  DDRB |= (1 << PB5);  // Set PB5 as output (for LED)
  DDRD = 0x00;         // Set all D port pins to input
}

void toggleLED() { PORTB ^= (1 << PB5); }
