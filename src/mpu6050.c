/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mpu6050.h"

#include "i2c.h"

static double accelDivisor = 1;
static double gyroDivisor = 1;

void initMPU6050() {
  i2cStart();
  i2cWrite(MPU6050_SLAVE_ADDR << 1);
  i2cWrite(MPU6050_PWR_MGMT_1);
  i2cWrite(MPU6050_WAKE); // wake
  i2cStop();
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

  i2cStart();                              // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0); // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_ACCEL_CONFIG); // RA
  // TODO (cameron): ACK
  i2cWrite((((uint8_t)config) << AFS_SEL_BIT_OFFSET));
  // TODO (cameron): ACK
  i2cStop(); // P
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

  i2cStart();
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0); // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_ACCEL_CONFIG); // RA
  // TODO (cameron): ACK
  i2cWrite((((uint8_t)config) << FS_SEL_BIT_OFFSET));
  // TODO (cameron): ACK
  i2cStop(); // P
}

void readAccelerometer(vec3 *accel) {
  i2cStart();                              // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0); // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_ACCEL_XOUT_H); // RA
  // TODO (cameron): ACK
  i2cStart();                              // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 1); // AD+R
  // TODO (cameron): ACK
  accel->x = ((i2cReadAck() << 8) | i2cReadAck()) / // DATA, ACK, DATA, ACK
             accelDivisor;
  accel->y = ((i2cReadAck() << 8) | i2cReadAck()) / // DATA, ACK, DATA, ACK
             accelDivisor;
  accel->z = ((i2cReadAck() << 8) | i2cReadNack()) / // DATA, ACK, DATA, NACK
             accelDivisor;
  i2cStop(); // P
}

void readGyrometer(vec3 *gyro) {
  i2cStart();                              // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0); // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_GRYO_XOUT_H); // RA
  // TODO (cameron): ACK
  i2cStart();                              // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 1); // AD+R
  // TODO (cameron): ACK
  gyro->x = ((i2cReadAck() << 8) | i2cReadAck()) / // DATA, ACK, DATA, ACK
            gyroDivisor;
  gyro->y = ((i2cReadAck() << 8) | i2cReadAck()) / // DATA, ACK, DATA, ACK
            gyroDivisor;
  gyro->z = ((i2cReadAck() << 8) | i2cReadNack()) / // DATA, ACK, DATA, NACK
            gyroDivisor;
  i2cStop(); // P
}

// FIXME (cameron): temperature is currently broken
void readTemperature(double *temp) {
  i2cStart();                              // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0); // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_TEMP_OUT_H); // RA
  // TODO (cameron): ACK
  i2cStart();                              // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 1); // AD+R
  // TODO (cameron): ACK
  double tempOut =
      (double)((i2cReadAck() << 8) | i2cReadNack()); // DATA, ACK, DATA, NACK
  i2cStop();                                         // P
  *temp = ((tempOut / 340) + 36.53);
};
