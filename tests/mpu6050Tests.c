/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mock_avr_io.h"
#include "mpu6050.h"
#include "unity.h"
#include "unity_fixture.h"

#define INIT_MEM 0x9F

TEST_GROUP(mpu6050Tests);

TEST_SETUP(mpu6050Tests) {
  TWSR = INIT_MEM;
  TWBR = INIT_MEM;
  TWCR = INIT_MEM;
  TWDR = INIT_MEM;
}

TEST_TEAR_DOWN(mpu6050Tests) {}

TEST(mpu6050Tests, initMPU6050) {}

TEST_GROUP_RUNNER(mpu6050Tests) {
  RUN_TEST_CASE(mpu6050Tests, initMPU6050);
  ;
}
