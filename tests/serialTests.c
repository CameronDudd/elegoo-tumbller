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

  UDR0 = 0xFF;
  // Simulate UDR0 ready to accept data
  UCSR0A = 0b00100000;
}

TEST_TEAR_DOWN(serialTests) {}

TEST(serialTests, usartInit) {
  usartInit();
  TEST_ASSERT_EQUAL_UINT8(0b01100111, UBRR0L);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, UBRR0H);
  TEST_ASSERT_EQUAL_UINT8(0b00011000, UCSR0B);
  TEST_ASSERT_EQUAL_UINT8(0b00000110, UCSR0C);
  TEST_ASSERT_EQUAL_UINT8(0b01100111, UBRR0);
}

TEST(serialTests, uartPrint) {
  // Nothing will be put into the buffer
  uartPrint("");
  TEST_ASSERT_EQUAL_UINT8(0b11111111, UDR0);
  uartPrint("a");
  TEST_ASSERT_EQUAL_UINT8(0b01100001, UDR0);
  uartPrint("ab");
  TEST_ASSERT_EQUAL_UINT8(0b01100010, UDR0);
  uartPrint("abc");
  TEST_ASSERT_EQUAL_UINT8(0b01100011, UDR0);
}

// TODO (cameron): It would be better to be able to check that UDR0 is called
// with every character instead of just the last one
TEST(serialTests, uartPrintf) {
  // Nothing will be put into the buffer
  uartPrintf("");
  TEST_ASSERT_EQUAL_UINT8(0b11111111, UDR0);
  uartPrintf("a");
  TEST_ASSERT_EQUAL_UINT8(0b01100001, UDR0);
  uartPrintf("ab");
  TEST_ASSERT_EQUAL_UINT8(0b01100010, UDR0);
  uartPrintf("abc");
  TEST_ASSERT_EQUAL_UINT8(0b01100011, UDR0);
  uartPrintf("%i", 0);
  TEST_ASSERT_EQUAL_UINT8(0b00110000, UDR0);
  uartPrintf("%i", 1);
  TEST_ASSERT_EQUAL_UINT8(0b00110001, UDR0);
  uartPrintf("%s", "abc");
  TEST_ASSERT_EQUAL_UINT8(0b01100011, UDR0);
}

TEST_GROUP_RUNNER(serialTests) {
  RUN_TEST_CASE(serialTests, usartInit);
  RUN_TEST_CASE(serialTests, uartPrint);
  RUN_TEST_CASE(serialTests, uartPrintf);
}
