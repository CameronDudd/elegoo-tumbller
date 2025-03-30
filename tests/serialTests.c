/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mock_avr_io.h"
#include "serial.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(serialTests);

TEST_SETUP(serialTests) {
  UBRR0 = 0xFF;
  UBRR0L = 0;
  UBRR0H = 0;
}

TEST_TEAR_DOWN(serialTests) {}

TEST(serialTests, usartInit) {
  usartInit();
  TEST_ASSERT_EQUAL_UINT8(0b01100111, UBRR0L);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, UBRR0H);
  TEST_ASSERT_EQUAL_UINT8(0b00011000, UCSR0B);
  TEST_ASSERT_EQUAL_UINT8(0b00001110, UCSR0C);
  TEST_ASSERT_EQUAL_UINT8(0b01100111, UBRR0);
}

TEST(serialTests, _uartTransmit) {}

TEST_GROUP_RUNNER(serialTests) {
  RUN_TEST_CASE(serialTests, usartInit);
  RUN_TEST_CASE(serialTests, usartInit);
}
