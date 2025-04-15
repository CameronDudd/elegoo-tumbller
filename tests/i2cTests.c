/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "i2c.h"
#include "mock_avr_io.h"
#include "unity.h"
#include "unity_fixture.h"

#define INIT_MEM 0x9F

TEST_GROUP(i2cTests);

TEST_SETUP(i2cTests) {
  TWSR = INIT_MEM;
  TWBR = INIT_MEM;
  // bit TWINT (7) on TWCR must be set or while loops will go on forever
  TWCR = INIT_MEM;
  TWDR = INIT_MEM;
}

TEST_TEAR_DOWN(i2cTests) {}

TEST(i2cTests, i2cInit) {
  i2cInit();
  TEST_ASSERT_EQUAL_UINT8(0b00000000, TWSR);
  TEST_ASSERT_EQUAL_UINT8(0b01001000, TWBR);
  TEST_ASSERT_EQUAL_UINT8(0b00000100, TWCR);
}

TEST(i2cTests, i2cStart) {
  i2cStart();
  TEST_ASSERT_EQUAL_UINT8(0b10100100, TWCR);
}

TEST(i2cTests, i2cStatus) {
  TWSR = START & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(START, i2cStatus());
  TWSR = START2 & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(START2, i2cStatus());
  TWSR = SLA_W_ACK & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(SLA_W_ACK, i2cStatus());
  TWSR = SLA_W_NACK & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(SLA_W_NACK, i2cStatus());
  TWSR = DATA_ACK & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(DATA_ACK, i2cStatus());
  TWSR = DATA_NACK & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(DATA_NACK, i2cStatus());
  TWSR = SLA_R_ACK & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(SLA_R_ACK, i2cStatus());
  TWSR = UNDEFINED & 0xF8;
  TEST_ASSERT_EQUAL_UINT8(UNDEFINED, i2cStatus());
}

TEST(i2cTests, i2cReadAck) {
  uint8_t actualTWDR = i2cReadAck();
  TEST_ASSERT_EQUAL_UINT8(0b11000100, TWCR);
  TEST_ASSERT_EQUAL_UINT8(INIT_MEM, actualTWDR);
}

TEST(i2cTests, i2cReadNack) {
  uint8_t actualTWDR = i2cReadNack();
  TEST_ASSERT_EQUAL_UINT8(0b10000100, TWCR);
  TEST_ASSERT_EQUAL_UINT8(INIT_MEM, actualTWDR);
}

TEST(i2cTests, i2cWrite) {
  i2cWrite(-2);
  TEST_ASSERT_EQUAL_UINT8(0b10000100, TWCR);
  TEST_ASSERT_EQUAL_UINT8(0b11111110, TWDR);

  i2cWrite(-1);
  TEST_ASSERT_EQUAL_UINT8(0b10000100, TWCR);
  TEST_ASSERT_EQUAL_UINT8(0b11111111, TWDR);

  i2cWrite(0x00);
  TEST_ASSERT_EQUAL_UINT8(0b10000100, TWCR);
  TEST_ASSERT_EQUAL_UINT8(0x00, TWDR);

  i2cWrite(0x01);
  TEST_ASSERT_EQUAL_UINT8(0b10000100, TWCR);
  TEST_ASSERT_EQUAL_UINT8(0x01, TWDR);

  i2cWrite(0x90);
  TEST_ASSERT_EQUAL_UINT8(0b10000100, TWCR);
  TEST_ASSERT_EQUAL_UINT8(0x90, TWDR);
}

TEST(i2cTests, i2cStop) {
  i2cStop();
  TEST_ASSERT_EQUAL_UINT8(0b10010100, TWCR);
}

TEST_GROUP_RUNNER(i2cTests) {
  RUN_TEST_CASE(i2cTests, i2cInit);
  RUN_TEST_CASE(i2cTests, i2cStart);
  RUN_TEST_CASE(i2cTests, i2cStatus);
  RUN_TEST_CASE(i2cTests, i2cReadAck);
  RUN_TEST_CASE(i2cTests, i2cReadNack);
  RUN_TEST_CASE(i2cTests, i2cWrite);
  RUN_TEST_CASE(i2cTests, i2cStop);
}
