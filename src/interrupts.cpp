/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "interrupts.hpp"

#include <avr/interrupt.h>

volatile unsigned long leftWheelPulses = 0;  // To store pulse count for the left wheel

void initInterrupts() {
  EIMSK |= (1 << INT0);                  // Enable INT0 (left wheel encoder)
  EICRA |= (1 << ISC01) | (1 << ISC00);  // Rising edge trigger for INT0 (left wheel)
  sei();                                 // enable interrupts
}

ISR(INT0_vect) {
  cli();              // disable interrupts
  leftWheelPulses++;  // increment left wheel pulses
  sei();              // enable interrupts
}
