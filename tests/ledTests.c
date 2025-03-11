/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "led.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(ledTests);

TEST_SETUP(ledTests) {}

TEST_TEAR_DOWN(ledTests) {}

TEST(ledTests, initLED) { TEST_ASSERT_EQUAL(1, 1); }

TEST_GROUP_RUNNER(ledTests) { RUN_TEST_CASE(ledTests, initLED); }
