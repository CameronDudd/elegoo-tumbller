/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "mock_avr_delay.h"

double total_us_delay = 0;
double total_ms_delay = 0;

void _delay_us(double __us) { total_us_delay += __us; }

void _delay_ms(double __ms) { total_ms_delay += __ms; }
