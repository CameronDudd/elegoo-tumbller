/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

class MotorController {
 public:
  MotorController();
  void enableMotors();
  void disableMotors();
  void setSpeed(uint8_t speed);
  void forward();
  void reverse();
  void stop();
};

#endif  // MOTOR_H
