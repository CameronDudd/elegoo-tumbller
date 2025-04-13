/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef BALANCE_H
#define BALANCE_H

#include "vectors.h"

double pitchPID(vec3 *accel, vec3 *gyro, double *desiredPitch);

#endif  // BALANCE_H
