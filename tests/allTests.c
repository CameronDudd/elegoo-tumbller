/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "unity_fixture.h"

static void _runAllTests(void) { RUN_TEST_GROUP(ledTests); }

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, _runAllTests); }
