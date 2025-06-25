/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"

#include "state.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#endif

float pitchPID(float *pitch, float *desiredPitch, float *dt) {
  static float integralError = 0.0f, previousError = 0.0f;

  float error = *desiredPitch - *pitch;
  integralError += (error * *dt);

  float derivativeError = (error - previousError) / *dt;
  previousError         = error;

  float output = (pitchPIDConstants.KP * error) + (pitchPIDConstants.KI * integralError) + (pitchPIDConstants.KD * derivativeError);

  if (*pitch <= -50 || 50 <= *pitch) output = 0;

  return output;
}
