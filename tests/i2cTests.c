/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "i2c.h"
#include "mock_avr_io.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(i2cTests);

TEST_SETUP(i2cTests) {
  TWSR = 0xFF;
  TWBR = 0xFF;
}

TEST_TEAR_DOWN(i2cTests) {}

TEST(i2cTests, i2cInit) {
  i2cInit();
  TEST_ASSERT_EQUAL_INT8(0b00000000, TWSR);
  TEST_ASSERT_EQUAL_INT8(0b01001000, TWBR);
}

TEST_GROUP_RUNNER(i2cTests) {
  RUN_TEST_CASE(i2cTests, i2cInit);
  ;
}
