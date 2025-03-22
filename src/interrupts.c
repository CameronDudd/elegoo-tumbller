/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#endif

volatile unsigned long leftWheelPulses;
volatile unsigned long rightWheelPulses;
volatile unsigned long leftWheelSpeed;
volatile unsigned long rightWheelSpeed;

void initEncoders() {
  EIMSK |= (1 << INT0);      // Enable INT0 (left wheel encoder)
  EICRA |= (1 << ISC00);     // Any (rising/falling) edge trigger for INT0 (left wheel)
  PCMSK2 |= (1 << PCINT20);  // Enable PCINT22 (right wheel encoder)
  PCICR |= (1 << PCIE2);     // Enable PCIE2 interrupts
  sei();                     // global enable interrupts
}

void initSpeedTimer() {
  /*
   * OCR1A Output Compare Register 1A
   * OCR1B Output Compare Register 1B
   */
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1A = 0;                                          // Normal port operation OC1A/OC1B disconnected
  TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);  // WGM12 (CTC1 TOP OCR1A), clkIO / 64 (from pre-scaler)

  // 16MHz / 64 = 250,000 ticks/sec
  // Want 100ms intervals
  // 100ms: x ticks / 250,000 = 0.1s
  // 100ms: x ticks = 250,000 * 0.1
  // 100ms: x ticks = 25,000
  OCR1A = 25000;
  OCR1B = 0;

  TIMSK1 |= (1 << OCIE1A);  // Output Compare A Match Interrupt Enable

  sei();  // global enable interrupts
}

ISR(INT0_vect) {
  cli();              // disable interrupts
  leftWheelPulses++;  // increment left wheel pulses
  sei();              // enable interrupts
}

ISR(PCINT2_vect) {
  cli();               // disable interrupts
  rightWheelPulses++;  // increment right wheel pulses
  sei();               // enable interrupts
}

ISR(TIMER1_COMPA_vect) {
  cli();                                    // disable interrupts
  leftWheelSpeed = leftWheelPulses * 10;    // same as / 0.1s
  rightWheelSpeed = rightWheelPulses * 10;  // same as / 0.1s
  leftWheelPulses = 0;                      // reset left wheel pulses
  rightWheelPulses = 0;                     // reset right wheel pulses
  sei();                                    // enable interrupts
}
