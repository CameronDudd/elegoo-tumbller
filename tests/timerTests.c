/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mock_avr_io.h"
#include "timer.h"
#include "unity.h"
#include "unity_fixture.h"

extern uint8_t interruptsEnabled;

TEST_GROUP(timerTests);

TEST_SETUP(timerTests) {}

TEST_TEAR_DOWN(timerTests) {}

TEST(timerTests, initTimers) {
  initTimers();
  TEST_ASSERT_EQUAL_UINT8(0b00000000, TCCR1A);
  TEST_ASSERT_EQUAL_UINT8(0b00001001, TCCR1B);
  TEST_ASSERT_EQUAL_UINT8(15999, OCR1A);
  TEST_ASSERT_EQUAL_UINT8(0, OCR1B);
  TEST_ASSERT_EQUAL_UINT8(0b00000010, TIMSK1);
  TEST_ASSERT_EQUAL_UINT(0, millis);
  TEST_ASSERT_EQUAL_UINT(1, interruptsEnabled);
}

TEST_GROUP_RUNNER(timerTests) { RUN_TEST_CASE(timerTests, initTimers); }
