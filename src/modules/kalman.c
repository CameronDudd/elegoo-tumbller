/*
 *   A huge thank you to Lauszus for their post on TKJ Electronics for help with
 *   implementing the Kalman filter for a balancing robot
 *   https://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it
 */

#include "kalman.h"

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void initKalmanFilter(Kalman_t *kf) {
  kf->angle = 0.0f;
  kf->gyroBias = 0.0f;
  kf->P[0][0] = 0;
  kf->P[0][1] = 99999.9f;
  kf->P[1][0] = 0;
  kf->P[1][1] = 99999.9f;
  kf->Q_angle = 0.001f;
  kf->Q_gyroBias = 0.003f;
  kf->R_measure = 0.03f;
}

float updateKalmanFilter(Kalman_t *kf, vec3 *accel, vec3 *gyro, float *dt) {
  kf->gyroRate = gyro->x - kf->gyroBias;
  kf->angle += *dt * kf->gyroRate;

  kf->P[0][0] +=
      *dt * (*dt * kf->P[1][1] - kf->P[0][1] - kf->P[1][0] + kf->Q_angle);
  kf->P[0][1] -= *dt * kf->P[1][1];
  kf->P[1][0] -= *dt * kf->P[1][1];
  kf->P[1][1] += *dt * kf->Q_gyroBias;

  float y = atan2(accel->y, accel->z) * 180.0 / M_PI - kf->angle;

  float S = kf->P[0][0] + kf->R_measure;

  float K0 = kf->P[0][0] / S;
  float K1 = kf->P[1][0] / S;

  kf->angle += K0 * y;
  kf->gyroBias += K1 * y;

  float P00_temp = kf->P[0][0];
  float P01_temp = kf->P[0][1];

  kf->P[0][0] -= K0 * P00_temp;
  kf->P[0][0] -= K0 * P01_temp;
  kf->P[0][0] -= K1 * P00_temp;
  kf->P[0][0] -= K1 * P01_temp;

  return kf->angle;
}
