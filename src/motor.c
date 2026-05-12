/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#include "motor.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <util/atomic.h>

#include "board.h"
#include "pwm.h"

volatile int32_t leftWheelPulses  = 0;
volatile int32_t rightWheelPulses = 0;

static void _setMotorDirectionForward(void) {
  L_MOTOR_DIR_PORT &= ~(1 << L_MOTOR_DIR_PIN);
  R_MOTOR_DIR_PORT &= ~(1 << R_MOTOR_DIR_PIN);
}

static void _setMotorDirectionReverse(void) {
  L_MOTOR_DIR_PORT |= (1 << L_MOTOR_DIR_PIN);
  R_MOTOR_DIR_PORT |= (1 << R_MOTOR_DIR_PIN);
}

static uint8_t _percentToDuty(uint8_t percent) {
  if (percent > 100) percent = 100;
  return (percent * 255) / 100;
}

void initMotors(void) {
  // Set outputs
  DDRB |= (1 << MOTOR_STBY_PIN) | (1 << L_MOTOR_DIR_PIN);
  DDRD |= (1 << L_MOTOR_PWM_PIN) | (1 << R_MOTOR_PWM_PIN) | (1 << R_MOTOR_DIR_PIN);

  // Init to LOW
  MOTOR_STBY_PORT &= ~(1 << MOTOR_STBY_PIN);

  L_MOTOR_DIR_PORT &= ~(1 << L_MOTOR_DIR_PIN);
  R_MOTOR_DIR_PORT &= ~(1 << R_MOTOR_DIR_PIN);
};

void initEncoders(void) {
  EIMSK |= (1 << INT0);      // Enable INT0 (left wheel encoder)
  EICRA |= (1 << ISC00);     // Any (rising/falling) edge trigger for INT0 (left wheel)
  PCMSK2 |= (1 << PCINT20);  // Enable PCINT20 (right wheel encoder)
  PCICR |= (1 << PCIE2);     // Enable PCIE2 interrupts
}

void resetEncoders(void) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    leftWheelPulses  = 0;
    rightWheelPulses = 0;
  }
}

void enableMotors(void) { MOTOR_STBY_PORT |= (1 << MOTOR_STBY_PIN); }

void disableMotors(void) {
  MOTOR_STBY_PORT &= ~(1 << MOTOR_STBY_PIN);
  pwmStopAll();
}

void setMotorsPercent(int8_t percent) {
  if (percent >= 0) {
    _setMotorDirectionForward();
  } else {
    _setMotorDirectionReverse();
    percent = -percent;
  }
  pwmSet(L_MOTOR_PWM_CHANNEL, _percentToDuty(percent));
  pwmSet(R_MOTOR_PWM_CHANNEL, _percentToDuty(percent));
}

void setMotorStop(void) { pwmStopAll(); }

int32_t getLeftWheelPulses(void) {
  int32_t tmp;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { tmp = leftWheelPulses; }
  return tmp;
}

int32_t getRightWheelPulses(void) {
  int32_t tmp;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { tmp = rightWheelPulses; }
  return tmp;
}

ISR(INT0_vect) {
  if ((L_MOTOR_DIR_PORT & (1 << L_MOTOR_DIR_PIN)) == 0) {
    leftWheelPulses++;
  } else {
    leftWheelPulses--;
  }
}

ISR(PCINT2_vect) {
  if ((R_MOTOR_DIR_PORT & (1 << R_MOTOR_DIR_PIN)) == 0) {
    rightWheelPulses++;
  } else {
    rightWheelPulses--;
  }
}
