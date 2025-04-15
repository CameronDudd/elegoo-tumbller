/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "i2c.h"

#include "constants.h"

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/io.h>
#endif

void i2cInit() {
  TWSR = 0x00;                           // prescaler 0 TWSR1:0 = 00
  TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2; // [2]: TWBR = 1/2 [(CPU / SCL) - 16]
  TWCR = (1 << TWEN);                    // enable i2c interface
}

void i2cStart() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // send START
  while (!(TWCR & (1 << TWINT))) { // wait for transmission (TWINT flag set)
  }
}

I2CStatus i2cStatus() { return (I2CStatus)(TWSR & 0xF8); }

uint8_t i2cReadAck() {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // enable ACK and start recv
  while (!(TWCR & (1 << TWINT))) {                 // wait for data
  }
  return TWDR; // return data
}

uint8_t i2cReadNack() {
  TWCR = (1 << TWINT) | (1 << TWEN); // NACK (no enable ACK) and start recv
  while (!(TWCR & (1 << TWINT))) {   // wait for data
  }
  return TWDR; // return data
}

void i2cWrite(uint8_t data) {
  TWDR = data;                       // load data
  TWCR = (1 << TWINT) | (1 << TWEN); // transmit
  while (!(TWCR & (1 << TWINT))) {   // wait for TWINT
  }
}

void i2cStop() {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // send STOP
}

/*
 * [2]:
 *   SCL freq = (CPU_CLOCK) / (16 + 2(TWBR)(PrescalerValue))
 *   16 + 2(TWBR)(PrescalerValue) = CPU / SCL
 *   TWBR = (1/2)((CPU / SCL) - 16)
 */
