/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "unity_fixture.h"

static void _runAllTests(void) {
  printf("\nLED Tests:       ");
  RUN_TEST_GROUP(ledTests);
  printf("\ni2c Tests:       ");
  RUN_TEST_GROUP(i2cTests);
  printf("\nMotor Tests:     ");
  RUN_TEST_GROUP(motorTests);
  printf("\nInterrupt Tests: ");
  RUN_TEST_GROUP(interruptsTests);
}

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, _runAllTests); }
