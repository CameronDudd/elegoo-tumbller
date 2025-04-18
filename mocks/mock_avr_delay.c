/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mock_avr_delay.h"

float total_us_delay = 0;
float total_ms_delay = 0;

void _delay_us(float __us) { total_us_delay += __us; }

void _delay_ms(float __ms) { total_ms_delay += __ms; }
