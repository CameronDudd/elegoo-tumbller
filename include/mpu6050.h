/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

/* SPI Data Format
 * | MSB |    |    |    |    |    |    | LSB |
 * | D7  | D6 | D5 | D4 | D3 | D2 | D1 | D0  |
 *
 * Burst Read Sequence
 * | Master | S | AD+W |     | RA |     | S | AD+R |     |      | ACK |      | NAK | P |
 * | Slave  |   |      | ACK |    | ACK |   |      | ACK | DATA |     | DATA |     |   |
 *
 * Burst Write Sequence
 * | Master | S | AD+W |     | RA |     | DATA |     | DATA |     | P |
 * | Slave  |   |      | ACK |    | ACK |      | ACK |      | ACK |   |
 *
 * | Signal  | Description     |
 * |---------|-----------------|
 * |       S | Start Condition |
 * |---------|-----------------|
 * |      AD | Slave I2C addr  |
 * |---------|-----------------|
 * |       W | Write Bit (0)   |
 * |---------|-----------------|
 * |       R | Read Bit (1)    |
 * |---------|-----------------|
 * |     ACK | Acknowledge     |
 * |---------|-----------------|
 * |    NACK | Not-Acknowledge |
 * |---------|-----------------|
 * |      RA | MPU-60X0 internal server address
 * |---------|-----------------|
 * |    DATA | TX/RX           |
 * |---------|-----------------|
 * |       P | Stop Condition  |
 * |---------|-----------------|
 */

#ifndef MPU6050_H
#define MPU6050_H

#define MPU6050_WAKE 0x00

#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_ACCEL_CONFIG 0x1C
#define FS_SEL_BIT_OFFSET 4
#define AFS_SEL_BIT_OFFSET 4

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

#define MPU6050_TEMP_OUT_H 0x41
#define MPU6050_TEMP_OUT_L 0x42

#define MPU6050_GRYO_XOUT_H 0x43
#define MPU6050_GRYO_XOUT_L 0x44
#define MPU6050_GRYO_YOUT_H 0x45
#define MPU6050_GRYO_YOUT_L 0x46
#define MPU6050_GRYO_ZOUT_H 0x47
#define MPU6050_GRYO_ZOUT_L 0x48

#define MPU6050_PWR_MGMT_1 0x6B

#define MPU6050_SLAVE_ADDR 0x68

#include "vectors.h"

// AFS_SEL=0 16,384 LSB/g
// AFS_SEL=1 8,192 LSB/g
// AFS_SEL=2 4,096 LSB/g
// AFS_SEL=3 2,048 LSB
typedef enum {
  RANGE_2G = 0,
  RANGE_4G = 1,
  RANGE_8G = 2,
  RANGE_16G = 3,
} ACCEL_CONFIG;

// FS_SEL=0 131 LSB/(º/s)
// FS_SEL=1 65.5 LSB/(º/s)
// FS_SEL=2 32.8 LSB/(º/s)
// FS_SEL=3 16.4 LSB/(º/s)
typedef enum {
  RANGE_250 = 0,
  RANGE_500 = 1,
  RANGE_1000 = 2,
  RANGE_2000 = 3,
} GYRO_CONFIG;

void initMPU6050();
void configureAccelerometer(ACCEL_CONFIG config);
void configureGyrometer(GYRO_CONFIG config);
void readAccelerometer(vec3* accel);
void readTemperature(double* temp);
void readGyrometer(vec3* gyro);

#endif  // MPU6050_H
