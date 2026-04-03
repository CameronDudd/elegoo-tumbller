/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "balance.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/interrupt.h>
#endif

float outputFromPID(PIDCtx *ctx, float value, float desiredValue, float dt) {
  float error = desiredValue - value;
  ctx->integralError += (error * dt);
  float derivativeError = (error - ctx->previousError) / dt;
  ctx->previousError    = error;
  return (ctx->KP * error) + (ctx->KI * ctx->integralError) + (ctx->KD * derivativeError);
}
