/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#include "mpu6050.h"

#include "i2c.h"

static float accelDivisor = 16384;  // 2G
static float gyroDivisor  = 131;    // RANGE 250

void mpu6050Init(void) {
  i2cWriteRegister(MPU6050_SLAVE_ADDR, MPU6050_PWR_MGMT_1, MPU6050_WAKE);
  i2cWriteRegister(MPU6050_SLAVE_ADDR, 0x1A, 0x03);
}

void configureAccelerometer(ACCEL_CONFIG config) {
  switch (config) {
    case RANGE_2G:
      accelDivisor = 16384;
      break;
    case RANGE_4G:
      accelDivisor = 8192;
      break;
    case RANGE_8G:
      accelDivisor = 4096;
      break;
    case RANGE_16G:
      accelDivisor = 2048;
      break;
    default:
      accelDivisor = 1;
      break;
  }

  i2cWriteRegister(MPU6050_SLAVE_ADDR, MPU6050_ACCEL_CONFIG, (((uint8_t)config) << AFS_SEL_BIT_OFFSET));
}

void configureGyrometer(GYRO_CONFIG config) {
  switch (config) {
    case RANGE_250:
      gyroDivisor = 131;
      break;
    case RANGE_500:
      gyroDivisor = 65.5;
      break;
    case RANGE_1000:
      gyroDivisor = 32.8;
      break;
    case RANGE_2000:
      gyroDivisor = 16.4;
      break;
    default:
      gyroDivisor = 1;
      break;
  }

  i2cWriteRegister(MPU6050_SLAVE_ADDR, MPU6050_ACCEL_CONFIG, (((uint8_t)config) << FS_SEL_BIT_OFFSET));
}

void readAccelerometer(vec3* accel) {
  uint8_t buffer[6];

  i2cReadRegisters(MPU6050_SLAVE_ADDR, MPU6050_ACCEL_XOUT_H, buffer, 6);

  int16_t rawX = (buffer[0] << 8) | buffer[1];
  int16_t rawY = (buffer[2] << 8) | buffer[3];
  int16_t rawZ = (buffer[4] << 8) | buffer[5];

  accel->x = (float)rawX / accelDivisor;
  accel->y = (float)rawY / accelDivisor;
  accel->z = (float)rawZ / accelDivisor;
}

void readGyrometer(vec3* gyro) {
  uint8_t buffer[6];

  i2cReadRegisters(MPU6050_SLAVE_ADDR, MPU6050_GYRO_XOUT_H, buffer, 6);

  int16_t rawX = (buffer[0] << 8) | buffer[1];
  int16_t rawY = (buffer[2] << 8) | buffer[3];
  int16_t rawZ = (buffer[4] << 8) | buffer[5];

  gyro->x = (float)rawX / gyroDivisor;
  gyro->y = (float)rawY / gyroDivisor;
  gyro->z = (float)rawZ / gyroDivisor;
}

void readTemperature(float* temp) {
  uint8_t buffer[2];
  i2cReadRegisters(MPU6050_SLAVE_ADDR, MPU6050_TEMP_OUT_H, buffer, 2);

  int16_t rawTemp = (buffer[0] << 8) | buffer[1];
  *temp           = ((float)rawTemp / 340.0) + 36.53;
}
