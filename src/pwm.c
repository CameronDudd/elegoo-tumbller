/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "pwm.h"

#include <avr/io.h>

#include "board.h"

void pwmInit(void) {
  /*
   * OCR0A Output compare register 0A
   * OCR0B Output compare register 0B
   */
  TCCR0A = 0;
  TCCR0B = 0;

  // WGM02:0 = 001 (Phase Correct PWM) 0xFF top, COM0A0 = 1 (Toggle OC0A on
  // Compare Match)
  TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
  TCCR0B = (1 << CS00);  // No prescaler, start timer

  OCR0A = 0;
  OCR0B = 0;
}

void pwmSet(uint8_t channel, uint8_t duty) {
  switch (channel) {
    case L_MOTOR_PWM_CHANNEL:
      OCR0A = duty;
      break;
    case R_MOTOR_PWM_CHANNEL:
      OCR0B = duty;
      break;
    default:
      break;
  }
}

void pwmStopAll(void) {
  OCR0A = 0;
  OCR0B = 0;
}
