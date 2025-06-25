/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#endif

volatile unsigned long millis = 0;

void initTimers() {
  /*
   * OCR1A Output Compare Register 1A
   * OCR1B Output Compare Register 1B
   */
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1A = 0;                            // Normal port operation OC1A/OC1B disconnected
  TCCR1B |= (1 << WGM12) | (1 << CS10);  // CTC Mode, No prescaler

  // (16MHz / 1) / 1000 - 1;
  OCR1A = 15999;
  OCR1B = 0;

  TIMSK1 |= (1 << OCIE1A);  // Output Compare A Match Interrupt Enable
}

ISR(TIMER1_COMPA_vect) {
  cli();        // disable interrupts
  millis += 1;  // increment millis
  sei();        // enable interrupts
}
