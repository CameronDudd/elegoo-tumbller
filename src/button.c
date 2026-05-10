/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "button.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <util/atomic.h>

#include "timer.h"

#define BUTTON_PIN PB2
#define DEBOUNCE_STATE_MS 100

static volatile bool buttonWasPressed      = false;
static volatile uint32_t lastInterruptTime = 0;

void buttonsInit(void) {
  DDRB &= ~(1 << BUTTON_PIN);  // Input
  PORTB |= (1 << BUTTON_PIN);  // Pull-up

  PCMSK0 |= (1 << PCINT2);  // Enable PCINT2 (D10 button)
  PCICR |= (1 << PCIE0);    // Enable PCIE0 interrupts
}

bool readButtonPressed(void) {
  bool status = false;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    if (buttonWasPressed) {
      buttonWasPressed = false;
      status           = true;
    }
  }
  return status;
}

ISR(PCINT0_vect) {
  uint32_t currentTime = getMillis();
  if ((currentTime - lastInterruptTime) > DEBOUNCE_STATE_MS) {
    bool currentState = !(PINB & (1 << BUTTON_PIN));

    if (currentState) {
      buttonWasPressed = true;
    }

    lastInterruptTime = currentTime;
  }
}
