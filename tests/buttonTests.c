/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "button.h"
#include "mock_avr_io.h"
#include "timer.h"
#include "unity.h"
#include "unity_fixture.h"

extern void PCINT0_vect();

TEST_GROUP(buttonTests);

TEST_SETUP(buttonTests) {
  millis = 501;
  interruptsEnabled = 0;
  numInterruptsTriggered = 0;
  PCMSK0 = 0;
  PCICR = 0;
}

TEST_TEAR_DOWN(buttonTests) {}

TEST(buttonTests, initButtons) {
  initButtons();
  TEST_ASSERT_EQUAL_UINT8(0b00000100, PCMSK0);
  TEST_ASSERT_EQUAL_UINT8(0b00000001, PCICR);
  TEST_ASSERT_TRUE(interruptsEnabled);
}

TEST(buttonTests, buttonPressUpdateState) {
  TEST_ASSERT_EQUAL(STDBY, state);
  PCINT0_vect();
  TEST_ASSERT_EQUAL(BALANCE, state);
  TEST_ASSERT_TRUE(interruptsEnabled);
}

TEST_GROUP_RUNNER(buttonTests) {
  RUN_TEST_CASE(buttonTests, initButtons);
  RUN_TEST_CASE(buttonTests, buttonPressUpdateState);
}
