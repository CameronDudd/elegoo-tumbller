/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#include "pid.h"

void resetPIDController(PIDController* pid) {
  pid->integral  = 0.0f;
  pid->lastError = 0.0f;
}

void initPIDController(PIDController* pid, float p, float i, float d, float dt, float limit) {
  pid->Kp    = p;
  pid->Ki    = i;
  pid->Kd    = d;
  pid->dt    = dt;
  pid->limit = limit;
  resetPIDController(pid);
}

float updatePIDController(PIDController* pid, float setPoint, float measuredValue) {
  float error = setPoint - measuredValue;
  pid->integral += error * pid->dt;

  if (pid->integral > pid->limit) {
    pid->integral = pid->limit;
  } else if (pid->integral < -pid->limit) {
    pid->integral = -pid->limit;
  }

  float derivative = (error - pid->lastError) / pid->dt;
  float output     = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * derivative);

  pid->lastError = error;
  return output;
}
