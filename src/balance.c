/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"
#include "interrupts.h"

#include <math.h>

#define KP 1.0
#define KI 0.0
#define KD 0.0

// TODO (cameron): use gyro for prediction
double pitchPID(vec3 *accel, double *desiredPitch) {

  static unsigned long lastMillis = 0;
  static double integralError = 0, previousError = 0;

  double dt = millis - lastMillis;
  lastMillis = millis;

  // Looking up is +'ve pitch
  double currentPitch = atan2(accel->y, accel->z) * 180.0 / M_PI;

  double error = *desiredPitch - currentPitch;
  integralError += (error * dt);
  double derivativeError = (error - previousError) / dt;
  previousError = error;
  return (KP * error) + (KI * integralError) + (KD * derivativeError);
}
