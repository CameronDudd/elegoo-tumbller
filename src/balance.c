/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"
#include "interrupts.h"

#include <math.h>

#define ALPHA 0.98
#define KP 3.5
#define KI 0.0
#define KD 0.005

double pitchPID(vec3 *accel, vec3 *gyro, double *desiredPitch) {

  static unsigned long lastMillis = 0;
  static double integralError = 0, previousError = 0;

  double dt = (millis - lastMillis) / 1000.0;
  lastMillis = millis;
  if (dt <= 0) {
    dt = 0.001;
  }

  double pitch = atan2(accel->y, accel->z) * 180.0 / M_PI;
  pitch = ALPHA * (pitch + gyro->x * dt) + (1 - ALPHA) * accel->x;

  double error = *desiredPitch - pitch;
  integralError += (error * dt);
  double derivativeError = (error - previousError) / dt;
  previousError = error;
  return (KP * error) + (KI * integralError) + (KD * derivativeError);
}
