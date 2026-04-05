/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include <avr/interrupt.h>
#include <util/atomic.h>

volatile uint32_t millis_count = 0;

void timersInit(void) {
  /*
   * OCR1A Output Compare Register 1A
   * OCR1B Output Compare Register 1B
   */
  TCCR1A = 0;                                          // Normal port operation OC1A/OC1B disconnected
  TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);  // CTC Mode, Prescaler 64

  // (16MHz / 64) / 1000 - 1 = 249;
  OCR1A = 249;
  OCR1B = 0;

  TIMSK1 |= (1 << OCIE1A);  // Output Compare A Match Interrupt Enable
}

uint32_t getMillis(void) {
  uint32_t tmp;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { tmp = millis_count; }
  return tmp;
}

ISR(TIMER1_COMPA_vect) {
  millis_count += 1;  // increment millis
}
