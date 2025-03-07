/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef I2C_H
#define I2C_H

#include <stdint.h>

// Implementations as seen by the documentation
enum class I2CStatus : uint8_t {
  START = 0x08,
  START2 = 0x10,
  SLA_W_ACK = 0x18,
  SLA_W_NACK = 0x20,
  DATA_ACK = 0x28,
  DATA_NACK = 0x30,
  SLA_R_ACK = 0x40,
  UNDEFINED = 0xFF,
};

void i2cInit();
void i2cStart();
I2CStatus i2cStatus();
uint8_t i2cReadAck();
uint8_t i2cReadNack();
void i2cWrite(uint8_t data);
void i2cStop();

#endif  // I2C_H
