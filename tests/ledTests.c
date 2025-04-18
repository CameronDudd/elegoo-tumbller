/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "led.h"
#include "mock_avr_delay.h"
#include "mock_avr_io.h"
#include "tests.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(ledTests);

TEST_SETUP(ledTests) {
  DDRB = 0x00;
  DDRD = 0xFF;
  PORTB = 0xFF;
  PORTD = 0xFF;
}

TEST_TEAR_DOWN(ledTests) {}

TEST(ledTests, initLED) {
  initLED();
  TEST_ASSERT_EQUAL_UINT8(0b00100000, DDRB);
  TEST_ASSERT_EQUAL_UINT8(0b00001000, DDRD);
}

TEST(ledTests, toggleOnBoardLED) {
  TEST_ASSERT_EQUAL_UINT8(0b11111111, PORTB);
  toggleOnBoardLED();
  TEST_ASSERT_EQUAL_UINT8(0b11011111, PORTB);
  toggleOnBoardLED();
  TEST_ASSERT_EQUAL_UINT8(0b11111111, PORTB);
  toggleOnBoardLED();
  TEST_ASSERT_EQUAL_UINT8(0b11011111, PORTB);
}

TEST(ledTests, sendColorLEDReset) {
  sendColorLEDReset();
  TEST_ASSERT_EQUAL_DOUBLE(100, total_us_delay);
  TEST_ASSERT_EQUAL_UINT8(0b11110111, PORTD);
}

TEST(ledTests, sendLEDColor){SKIP}

TEST(ledTests, sendLEDColors){SKIP}

TEST(ledTests, flashLEDColors){SKIP}

TEST_GROUP_RUNNER(ledTests) {
  RUN_TEST_CASE(ledTests, initLED);
  RUN_TEST_CASE(ledTests, toggleOnBoardLED);
  RUN_TEST_CASE(ledTests, sendColorLEDReset);
  RUN_TEST_CASE(ledTests, sendLEDColor);
  RUN_TEST_CASE(ledTests, sendLEDColors);
  RUN_TEST_CASE(ledTests, flashLEDColors);
}
