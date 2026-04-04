/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "i2c.h"

#include <avr/io.h>

#define F_CPU 16000000UL   // 16 MHz
#define SCL_CLOCK 100000L  // 100kHz
#define I2C_TIMEOUT 10000

static uint8_t _i2cWait(void) {
  uint16_t timeout = I2C_TIMEOUT;
  while (!(TWCR & (1 << TWINT)) && timeout--) {
  }
  return (timeout == 0) ? 0 : 1;
}

static void _i2cStart(void) {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);  // send START
  _i2cWait();
}

static void _i2cStop(void) {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);  // send STOP
}

static void _i2cWrite(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  _i2cWait();
}

static uint8_t _i2cRead(uint8_t ack) {
  if (ack) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  } else {
    TWCR = (1 << TWINT) | (1 << TWEN);
  }
  _i2cWait();
  return TWDR;
}

void i2cInit(void) {
  TWSR = 0x00;                            // prescaler 0 TWSR1:0 = 00
  TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;  // [2]: TWBR = 1/2 [(CPU / SCL) - 16]
  TWCR = (1 << TWEN);                     // enable i2c interface
}

I2CStatus i2cStatus(void) { return (I2CStatus)(TWSR & 0xF8); }

void i2cReadRegisters(uint8_t devAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length) {
  _i2cStart();
  _i2cWrite(devAddr << 1);
  _i2cWrite(regAddr);

  _i2cStart();
  _i2cWrite((devAddr << 1) | 1);  // Slave Address + Read (1)

  // ACK for all bytes except for last (NACK)
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = _i2cRead(i < (length - 1));
  }

  _i2cStop();
}

void i2cWriteRegister(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
  _i2cStart();
  _i2cWrite(devAddr << 1);  // Slave Address + Write (0)
  _i2cWrite(regAddr);
  _i2cWrite(data);
  _i2cStop();
}

/*
 * [2]:
 *   SCL freq = (CPU_CLOCK) / (16 + 2(TWBR)(PrescalerValue))
 *   16 + 2(TWBR)(PrescalerValue) = CPU / SCL
 *   TWBR = (1/2)((CPU / SCL) - 16)
 */
