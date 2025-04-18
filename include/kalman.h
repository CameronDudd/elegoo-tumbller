/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef KALMAN_H
#define KALMAN_H

#include "vectors.h"
typedef struct {
  float angle;
  float gyroBias;
  float gyroRate;
  float P[2][2];
  float Q_angle;
  float Q_gyroBias;
  float R_measure;
} Kalman_t;

void initKalmanFilter(Kalman_t *kf);

float updateKalmanFilter(Kalman_t *kf, vec3 *accel, vec3 *gyro, float *dt);

#endif  // KALMAN_H
