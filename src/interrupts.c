/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "interrupts.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#endif

volatile unsigned long leftWheelPulses;
volatile unsigned long rightWheelPulses;

void initEncoders() {
  EIMSK |= (1 << INT0); // Enable INT0 (left wheel encoder)
  EICRA |=
      (1 << ISC00); // Any (rising/falling) edge trigger for INT0 (left wheel)
  PCMSK2 |= (1 << PCINT20); // Enable PCINT22 (right wheel encoder)
  PCICR |= (1 << PCIE2);    // Enable PCIE2 interrupts
  sei();                    // global enable interrupts
}

ISR(INT0_vect) {
  cli();             // disable interrupts
  leftWheelPulses++; // increment left wheel pulses
  sei();             // enable interrupts
}

ISR(PCINT2_vect) {
  cli();              // disable interrupts
  rightWheelPulses++; // increment right wheel pulses
  sei();              // enable interrupts
}
