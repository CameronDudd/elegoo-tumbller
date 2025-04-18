/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"

#define KP 10.0
#define KI 0.0
#define KD 0.0

float pitchPID(float *pitch, float *desiredPitch, float *dt) {

  static float integralError = 0, previousError = 0;

  float error = *desiredPitch - *pitch;
  integralError += (error * *dt);

  float derivativeError = (error - previousError) / *dt;
  previousError = error;

  float output = (KP * error) + (KI * integralError) + (KD * derivativeError);

  if (*pitch <= -75 || 75 <= *pitch)
    output = 0;

  return output;
}
