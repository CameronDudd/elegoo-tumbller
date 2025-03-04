/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include <stdio.h>
#include <util/delay.h>

#include "interrupts.hpp"
#include "motor.hpp"
#include "serial.hpp"

extern volatile unsigned long leftWheelPulses;

char outputBuff[200] = {};

int main() {
  initInterrupts();

  Serial serial = Serial();
  MotorController motorController = MotorController();
  motorController.enableMotors();

  while (1) {
    sprintf(outputBuff, "%lu\n", leftWheelPulses);
    serial.uart_print(outputBuff);

    motorController.setSpeed(128);
    _delay_ms(1000);

    motorController.setSpeed(0);
    _delay_ms(1000);

    // motorController.setSpeed(255);
    // _delay_ms(1000);
  }

  motorController.disableMotors();

  return 0;
}
