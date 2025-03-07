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

#include <stdint.h>

class MPU6050Controller {
 public:
  MPU6050Controller();
  ~MPU6050Controller();
  void readAccelerometer(int16_t* ax, int16_t* ay, int16_t* az);
  void readTemperature(double* temp);
  void readGyrometer(int16_t* gx, int16_t* gy, int16_t* gz);
};

#endif  // MPU6050_H
