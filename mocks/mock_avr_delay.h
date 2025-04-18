/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOCK_AVR_DELAY_H
#define MOCK_AVR_DELAY_H

extern float total_us_delay;
extern float total_ms_delay;

void _delay_us(float __us);
void _delay_ms(float __ms);

#endif  // MOCK_AVR_DELAY_H
