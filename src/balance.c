/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"
#include "interrupts.h"

#include <math.h>

#define KP 12.5
#define KI 0.001
#define KD 0.01
#define ALPHA 0.98
#define MAX_OUTPUT 90

double pitchPID(vec3 *accel, vec3 *gyro, double *desiredPitch) {

  static unsigned long lastMillis = 0;
  static double integralError = 0, previousError = 0, previousPitch = 0;

  double dt = (millis - lastMillis) / 1000.0;
  lastMillis = millis;
  if (dt <= 0) {
    dt = 0.001;
  }

  double accPitch = atan2(accel->y, accel->z) * 180.0 / M_PI;
  double pitch =
      ALPHA * (previousPitch + gyro->x * dt) + (1 - ALPHA) * accPitch;
  previousPitch = pitch;

  double error = *desiredPitch - pitch;
  integralError += (error * dt);

  if (integralError > 90)
    integralError = 90;
  if (integralError < -90)
    integralError = 90;

  double derivativeError = (error - previousError) / dt;
  previousError = error;
  double output = (KP * error) + (KI * integralError) + (KD * derivativeError);
  if (output > MAX_OUTPUT)
    output = MAX_OUTPUT;
  if (output < -MAX_OUTPUT)
    output = -MAX_OUTPUT;

  if (pitch <= -75 || 75 <= pitch)
    output = 0;

  return output;
}
