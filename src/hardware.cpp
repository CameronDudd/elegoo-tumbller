/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "hardware.hpp"

#include <avr/io.h>

Hardware::Hardware() {
  DDRB |= (1 << PB5);  // Set PB5 as output (for LED)
  DDRD = 0x00;         // Set all D port pins to input
}

void Hardware::toggle_led() {
  PORTB ^= (1 << PB5);
  ;
}
