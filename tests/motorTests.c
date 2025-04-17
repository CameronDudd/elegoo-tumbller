/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mock_avr_io.h"
#include "motor.h"
#include "tests.h"
#include "timer.h"
#include "unity.h"
#include "unity_fixture.h"

extern uint8_t interruptsEnabled;

TEST_GROUP(motorTests);

TEST_SETUP(motorTests) {
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  OCR0A = 0xFF;
  OCR0B = 0xFF;
  DDRB = 0x00;
  DDRD = 0x00;
  PORTB = 0xFF;
  PORTD = 0xFF;
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

TEST_TEAR_DOWN(motorTests) {}

TEST(motorTests, initPWM) {
  initPWM();
  TEST_ASSERT_EQUAL_UINT8(0b10100001, TCCR0A);
  TEST_ASSERT_EQUAL_UINT8(0b00000001, TCCR0B);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0A);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0B);
}

TEST(motorTests, initMotors) {
  initMotors();
  TEST_ASSERT_EQUAL_UINT8(0b00010001, DDRB);
  TEST_ASSERT_EQUAL_UINT8(0b11100000, DDRD);
  TEST_ASSERT_EQUAL_UINT8(0b11101110, PORTB);
  TEST_ASSERT_EQUAL_UINT8(0b00011111, PORTD);
}

TEST(motorTests, initEncoders) {
  initEncoders();
  TEST_ASSERT_EQUAL_UINT(0b00000001, EIMSK);
  TEST_ASSERT_EQUAL_UINT(0b00000001, EICRA);
  TEST_ASSERT_EQUAL_UINT(0b00010000, PCMSK2);
  TEST_ASSERT_EQUAL_UINT(0b00000100, PCICR);
  TEST_ASSERT_EQUAL_UINT(0, millis);
  TEST_ASSERT_EQUAL_UINT(1, interruptsEnabled);
}

TEST(motorTests, enableMotors) {
  PORTB = 0;
  enableMotors();
  TEST_ASSERT_EQUAL_UINT8(0b00000001, PORTB);
}

TEST(motorTests, disableMotors) {
  disableMotors();
  TEST_ASSERT_EQUAL_UINT8(0b11111110, PORTB);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0A);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0B);
}

TEST(motorTests, setSpeed) {
  setSpeed(0b00000000);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0A);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0B);

  setSpeed(0b10101010);
  TEST_ASSERT_EQUAL_UINT8(0b10101010, OCR0A);
  TEST_ASSERT_EQUAL_UINT8(0b10101010, OCR0B);

  setSpeed(0b11111111);
  TEST_ASSERT_EQUAL_UINT8(0b11111111, OCR0A);
  TEST_ASSERT_EQUAL_UINT8(0b11111111, OCR0B);
}

TEST(motorTests, forward) {
  PORTB = 0x00;
  PORTD = 0x00;
  forward();
  TEST_ASSERT_EQUAL_UINT8(0b00000000, PORTB);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, PORTD);

  PORTB = 0xFF;
  PORTD = 0xFF;
  forward();
  TEST_ASSERT_EQUAL_UINT8(0b11101111, PORTB);
  TEST_ASSERT_EQUAL_UINT8(0b01111111, PORTD);
}

TEST(motorTests, reverse) {
  PORTB = 0x00;
  PORTD = 0x00;
  reverse();
  TEST_ASSERT_EQUAL_UINT8(0b00010000, PORTB);
  TEST_ASSERT_EQUAL_UINT8(0b10000000, PORTD);

  PORTB = 0xFF;
  PORTD = 0xFF;
  reverse();
  TEST_ASSERT_EQUAL_UINT8(0b11111111, PORTB);
  TEST_ASSERT_EQUAL_UINT8(0b11111111, PORTD);
}

TEST(motorTests, stop) {
  stop();
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0A);
  TEST_ASSERT_EQUAL_UINT8(0b00000000, OCR0B);
}

TEST(motorTests, ISR_INT0_vect){SKIP}

TEST(motorTests, ISR_PCINT2_vect){SKIP}

TEST(motorTests, ISR_TIMER1_COMPA_vect){SKIP}

TEST_GROUP_RUNNER(motorTests) {
  RUN_TEST_CASE(motorTests, initPWM);
  RUN_TEST_CASE(motorTests, initMotors);
  RUN_TEST_CASE(motorTests, initEncoders);
  RUN_TEST_CASE(motorTests, enableMotors);
  RUN_TEST_CASE(motorTests, disableMotors);
  RUN_TEST_CASE(motorTests, setSpeed);
  RUN_TEST_CASE(motorTests, forward);
  RUN_TEST_CASE(motorTests, reverse);
  RUN_TEST_CASE(motorTests, stop);
  RUN_TEST_CASE(motorTests, ISR_INT0_vect);
  RUN_TEST_CASE(motorTests, ISR_PCINT2_vect);
  RUN_TEST_CASE(motorTests, ISR_TIMER1_COMPA_vect);
}
