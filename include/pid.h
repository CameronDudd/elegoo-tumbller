/*
 *   Copyright (c) 2026 Cameron Dudd
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

void resetPIDController(PIDController* pid);
void initPIDController(PIDController* pid, float p, float i, float d, float dt, float limit);
float updatePIDController(PIDController* pid, float setPoint, float measuredValue);

#endif  // PID_H
