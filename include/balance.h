/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "vectors.h"

#ifndef BALANCE_H
#define BALANCE_H

double pitchPID(vec3 *accel, vec3 *gyro, double *desiredPitch);

#endif  // BALANCE_H
