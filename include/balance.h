/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef BALANCE_H
#define BALANCE_H

typedef struct {
  float KP;
  float KI;
  float KD;
  float integralError;
  float previousError;
} PIDCtx;

float outputFromPID(PIDCtx *ctx, float value, float desiredValue, float dt);

#endif  // BALANCE_H
