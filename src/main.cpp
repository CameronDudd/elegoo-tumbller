/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include <stdio.h>
#include <util/delay.h>

#include "interrupts.hpp"
#include "motor.hpp"
#include "serial.hpp"

extern volatile unsigned long leftWheelSpeed;
extern volatile unsigned long rightWheelSpeed;

char outputBuff[200] = {};

int main() {
  initEncoders();
  initSpeedTimer();

  Serial serial = Serial();
  MotorController motorController = MotorController();

  // motorController.enableMotors();
  // motorController.setSpeed(255);  2550
  // motorController.setSpeed(200);  2000
  // motorController.setSpeed(175);  1730
  // motorController.setSpeed(150);  1470
  // motorController.setSpeed(125);  1220
  // motorController.setSpeed(100);   960
  // motorController.setSpeed(75);    700

  while (1) {
    sprintf(outputBuff, "Left-Speed:%lu pulses/s Right-Speed:%lu pulses/s\r\n", leftWheelSpeed, rightWheelSpeed);
    serial.uart_print(outputBuff);

    // _delay_ms(1000);

    // motorController.setSpeed(0);
    // _delay_ms(1000);

    // motorController.setSpeed(255);
    // _delay_ms(1000);
  }

  motorController.disableMotors();

  return 0;
}
