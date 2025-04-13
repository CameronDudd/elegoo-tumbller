/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOCK_AVR_DELAY_H
#define MOCK_AVR_DELAY_H

extern double total_us_delay;
extern double total_ms_delay;

void _delay_us(double __us);
void _delay_ms(double __ms);

#endif  // MOCK_AVR_DELAY_H
