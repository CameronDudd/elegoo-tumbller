/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "led.h"
#include "mock_avr_io.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(ledTests);

TEST_SETUP(ledTests) {
  DDRB = 0x00;
  DDRD = 0xFF;
  PORTB = 0xFF;
}

TEST_TEAR_DOWN(ledTests) {}

TEST(ledTests, initLED) {
  initLED();
  TEST_ASSERT_EQUAL_INT8(0b00100000, DDRB);
  TEST_ASSERT_EQUAL_INT8(0, DDRD);
}

TEST(ledTests, toggleLED) {
  TEST_ASSERT_EQUAL_INT8(0b11111111, PORTB);
  toggleLED();
  TEST_ASSERT_EQUAL_INT8(0b11011111, PORTB);
  toggleLED();
  TEST_ASSERT_EQUAL_INT8(0b11111111, PORTB);
  toggleLED();
  TEST_ASSERT_EQUAL_INT8(0b11011111, PORTB);
}

TEST_GROUP_RUNNER(ledTests) {
  RUN_TEST_CASE(ledTests, initLED);
  RUN_TEST_CASE(ledTests, toggleLED);
}
