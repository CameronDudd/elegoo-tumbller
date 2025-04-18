/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"

#define KP 10.0
#define KI 0.0
#define KD 0.0

double pitchPID(double *pitch, double *desiredPitch, double *dt) {

  static double integralError = 0, previousError = 0;

  double error = *desiredPitch - *pitch;
  integralError += (error * *dt);

  double derivativeError = (error - previousError) / *dt;
  previousError = error;

  double output = (KP * error) + (KI * integralError) + (KD * derivativeError);

  if (*pitch <= -75 || 75 <= *pitch)
    output = 0;

  return output;
}
