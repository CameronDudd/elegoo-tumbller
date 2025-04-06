/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "motor.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#endif

volatile unsigned long leftWheelPulses;
volatile unsigned long rightWheelPulses;

// TODO (cameron): better comments / documentation

void initPWM() {
  /*
   * OCR0A Output compare register 0A
   * OCR0B Output compare register 0B
   */
  TCCR0A = 0;
  TCCR0B = 0;

  // WGM02:0 = 001 (Phase Correct PWM) 0xFF top, COM0A0 = 1 (Toggle OC0A on
  // Compare Match)
  TCCR0A = (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
  TCCR0B = (1 << CS00); // No prescaler, start timer

  OCR0A = 0; // Duty cycle for PD6
  OCR0B = 0; // Duty cycle for PD5
};

void initMotors() {
  /*
   * PB0 STBY
   * PD5 Left  motor PWM output control pin
   * PD6 Right motor PWM output control pin
   * TODO (cameron): D7  Right motor rotation direction control pin
   * TODO (cameron): D12 Left  motor rotation direction control pin
   */

  // Enable motor output pins
  // PD5 & PD6 also set OC0A and OC0B for PWM
  DDRB |= (1 << PB0) | (1 << L_MOTOR_ROTATION_DIRECTION);
  DDRD |= (1 << PD5) | (1 << PD6) | (1 << R_MOTOR_ROTATION_DIRECTION);

  // tie all output low
  PORTB &= ~((1 << PB0) | (1 << L_MOTOR_ROTATION_DIRECTION));
  PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << R_MOTOR_ROTATION_DIRECTION));
};

void initEncoders() {
  EIMSK |= (1 << INT0); // Enable INT0 (left wheel encoder)
  EICRA |=
      (1 << ISC00); // Any (rising/falling) edge trigger for INT0 (left wheel)
  PCMSK2 |= (1 << PCINT20); // Enable PCINT22 (right wheel encoder)
  PCICR |= (1 << PCIE2);    // Enable PCIE2 interrupts
  sei();                    // global enable interrupts
}

void enableMotors() {
  PORTB |= (1 << PB0); // set PB0 HIGH
}

void disableMotors() {
  PORTB &= ~(1 << PB0); // set PB0 LOW
  OCR0A = 0;
  OCR0B = 0;
}

void setSpeed(uint8_t speed) {
  OCR0A = speed;
  OCR0B = speed;
}

void forward() {
  PORTB &= ~(1 << L_MOTOR_ROTATION_DIRECTION);
  PORTD &= ~(1 << R_MOTOR_ROTATION_DIRECTION);
}

void reverse() {
  PORTB |= (1 << L_MOTOR_ROTATION_DIRECTION);
  PORTD |= (1 << R_MOTOR_ROTATION_DIRECTION);
}

void stop() { // TODO (cameron):
  OCR0A = 0;
  OCR0B = 0;
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
