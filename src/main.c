/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "interrupts.h"
#include "motor.h"

int main() {
  initEncoders();
  initSpeedTimer();
  initPWM();
  initMotors();
  enableMotors();
  setSpeed(100);
  return 0;
}
