/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "interrupts.h"
#include "mock_avr_io.h"
#include "tests.h"
#include "unity.h"
#include "unity_fixture.h"

extern uint8_t interruptsEnabled;

TEST_GROUP(interruptsTests);

TEST_SETUP(interruptsTests) {
  EIMSK = 0x00;
  EICRA = 0x00;
  PCMSK2 = 0x00;
  PCICR = 0x00;
  TCCR1A = 0xFF;
  TCCR1B = 0xFF;
  OCR1A = 0xFF;
  OCR1B = 0xFF;
  TIMSK1 = 0x00;
  interruptsEnabled = 0;
}

TEST_TEAR_DOWN(interruptsTests) {}

TEST(interruptsTests, initEncoders) {
  initEncoders();
  TEST_ASSERT_EQUAL_UINT(0b00000001, EIMSK);
  TEST_ASSERT_EQUAL_UINT(0b00000001, EICRA);
  TEST_ASSERT_EQUAL_UINT(0b00010000, PCMSK2);
  TEST_ASSERT_EQUAL_UINT(0b00000100, PCICR);
  TEST_ASSERT_EQUAL_UINT(1, interruptsEnabled);
}

TEST(interruptsTests, initSpeedTimer) {
  initSpeedTimer();
  TEST_ASSERT_EQUAL_UINT8(0b00000000, TCCR1A);
  TEST_ASSERT_EQUAL_UINT8(0b00001011, TCCR1B);
  TEST_ASSERT_EQUAL_UINT8(25000, OCR1A);
  TEST_ASSERT_EQUAL_UINT8(0, OCR1B);
  TEST_ASSERT_EQUAL_UINT8(0b00000010, TIMSK1);
  TEST_ASSERT_EQUAL_UINT(1, interruptsEnabled);
}

TEST(interruptsTests, ISR_INT0_vect){SKIP}

TEST(interruptsTests, ISR_PCINT2_vect){SKIP}

TEST(interruptsTests, ISR_TIMER1_COMPA_vect){SKIP}

TEST_GROUP_RUNNER(interruptsTests) {
  RUN_TEST_CASE(interruptsTests, initEncoders);
  RUN_TEST_CASE(interruptsTests, initSpeedTimer);
  RUN_TEST_CASE(interruptsTests, ISR_INT0_vect);
  RUN_TEST_CASE(interruptsTests, ISR_PCINT2_vect);
  RUN_TEST_CASE(interruptsTests, ISR_TIMER1_COMPA_vect);
}
