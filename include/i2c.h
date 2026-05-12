/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#ifndef I2C_H
#define I2C_H

#include <stdint.h>

// Implementations as seen by the documentation
typedef enum {
  START      = 0x08,
  START2     = 0x10,
  SLA_W_ACK  = 0x18,
  SLA_W_NACK = 0x20,
  DATA_ACK   = 0x28,
  DATA_NACK  = 0x30,
  SLA_R_ACK  = 0x40,
  UNDEFINED  = 0xF8,
} I2CStatus;

void i2cInit(void);
I2CStatus i2cStatus(void);
void i2cReadRegisters(uint8_t devAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length);
void i2cWriteRegister(uint8_t devAddr, uint8_t regAddr, uint8_t data);

#endif  // I2C_H
