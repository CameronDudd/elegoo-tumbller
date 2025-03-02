/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "motor.hpp"

#include <avr/io.h>

// TODO (cameron): better comments / documentation

static void _initPWM() {
  /*
   * OCR0A Output compare register A
   * OCR0B Output compare register B
   */
  TCCR0A = 0;
  TCCR0B = 0;

  // WGM02:0 = 001 (Phase Correct PWM) 0xFF top, COM0A0 = 1 (Toggle OC0A on Compare Match)
  TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
  TCCR0B = (1 << CS00);  // No prescaler, start timer

  OCR0A = 0;  // Duty cycle for PD6
  OCR0B = 0;  // Duty cycle for PD5
};

static void _initMotors() {
  /*
   * PB0 STBY
   * PD5 Left  motor PWM output control pin
   * PD6 Right motor PWM output control pin
   * TODO (cameron): D7  Right motor rotation direction control pin
   * TODO (cameron): D12 Left  motor rotation direction control pin
   */

  // Enable motor output pins
  // PD5 & PD6 also set OC0A and OC0B for PWM
  DDRB |= (1 << PB0);
  DDRD |= (1 << PD5) | (1 << PD6);

  // tie all output low
  PORTB &= ~(1 << PB0);
  PORTD &= ~((1 << PD5) | (1 << PD6));
};

// MotorController
MotorController::MotorController() {
  _initPWM();
  _initMotors();
}

void MotorController::enableMotors() {
  PORTB |= (1 << PB0);  // set PB0 HIGH
}

void MotorController::disableMotors() {
  PORTB &= ~(1 << PB0);  // set PB0 LOW
  OCR0A = 0;
  OCR0B = 0;
}

void MotorController::setSpeed(uint8_t speed) {
  OCR0A = speed;
  OCR0B = speed;
}

void MotorController::forward() {}  // TODO (cameron):

void MotorController::stop() {  // TODO (cameron):
  OCR0A = 0;
  OCR0B = 0;
}
