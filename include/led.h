/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifdef UNIT_TEST
#include "mock_avr_io.h"
#else
#include <avr/io.h>
#endif

#ifndef LED_H
#define LED_H

void initLED();
void toggleLED();

#endif  // LED_H
