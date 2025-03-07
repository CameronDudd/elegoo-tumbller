/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mpu6050.hpp"

#include "i2c.hpp"

static void _initMPU6050() {
  i2cStart();
  i2cWrite(MPU6050_SLAVE_ADDR << 1);
  i2cWrite(MPU6050_PWR_MGMT_1);
  i2cStop();
}

MPU6050Controller::MPU6050Controller() { _initMPU6050(); };

void MPU6050Controller::readAccelerometer(int16_t* ax, int16_t* ay, int16_t* az) {
  i2cStart();                               // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0);  // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_ACCEL_XOUT_H);  // RA
  // TODO (cameron): ACK
  i2cStart();                               // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 1);  // AD+R
  // TODO (cameron): ACK
  *ax = (i2cReadAck() << 8) | i2cReadAck();   // DATA, ACK, DATA, ACK
  *ay = (i2cReadAck() << 8) | i2cReadAck();   // DATA, ACK, DATA, ACK
  *az = (i2cReadAck() << 8) | i2cReadNack();  // DATA, ACK, DATA, NACK
  i2cStop();                                  // P
}

// FIXME (cameron): temperature is currently broken
void MPU6050Controller::readTemperature(double* temp) {
  i2cStart();                               // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0);  // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_TEMP_OUT_H);  // RA
  // TODO (cameron): ACK
  i2cStart();                               // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 1);  // AD+R
  // TODO (cameron): ACK
  double tempOut = (double)((i2cReadAck() << 8) | i2cReadNack());  // DATA, ACK, DATA, NACK
  i2cStop();                                                       // P
  *temp = ((tempOut / 340) + 36.53);
};

void MPU6050Controller::readGyrometer(int16_t* gx, int16_t* gy, int16_t* gz) {
  i2cStart();                               // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 0);  // AD+W
  // TODO (cameron): ACK
  i2cWrite(MPU6050_GRYO_XOUT_H);  // RA
  // TODO (cameron): ACK
  i2cStart();                               // S
  i2cWrite((MPU6050_SLAVE_ADDR << 1) | 1);  // AD+R
  // TODO (cameron): ACK
  *gx = (i2cReadAck() << 8) | i2cReadAck();   // DATA, ACK, DATA, ACK
  *gy = (i2cReadAck() << 8) | i2cReadAck();   // DATA, ACK, DATA, ACK
  *gz = (i2cReadAck() << 8) | i2cReadNack();  // DATA, ACK, DATA, NACK
  i2cStop();                                  // P
}
