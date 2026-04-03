/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "button.h"

#include "state.h"
#include "timer.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#endif

#define DEBOUNCE_STATE_MS 500

static volatile unsigned long lastPressed = 0;

void initButtons() {
  PCMSK0 |= (1 << PCINT2);  // Enable PCINT2 (D10 button)
  PCICR |= (1 << PCIE0);    // Enable PCIE0 interrupts
}

ISR(PCINT0_vect) {
  cli();                                             // disable interrupts
  if ((millis - lastPressed) > DEBOUNCE_STATE_MS) {  // simple debounce
    state       = (state + 1) % NUM_STATES;          // toggle through states
    lastPressed = millis;
  }
  sei();  // enable interrupts
}
