/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include <util/delay.h>

#include "motor.hpp"

int main() {
  MotorController motorController = MotorController();
  motorController.enableMotors();

  while (1) {
    motorController.setSpeed(0);
    _delay_ms(1000);

    motorController.setSpeed(128);
    _delay_ms(1000);

    motorController.setSpeed(0);
    _delay_ms(1000);

    motorController.setSpeed(255);
    _delay_ms(1000);
  }

  motorController.disableMotors();

  return 0;
}
