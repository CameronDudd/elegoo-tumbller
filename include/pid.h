/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef PID_H
#define PID_H

typedef struct {
  float Kp, Ki, Kd;
  float integral;
  float lastError;
  float limit;
  float dt;
} PIDController;

void initPIDController(PIDController* pid, float p, float i, float d, float dt, float limit);
float updatePIDController(PIDController* pid, float setPoint, float measuredValue);

#endif  // PID_H
