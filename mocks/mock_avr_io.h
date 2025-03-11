/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MOCK_AVR_IO_H
#define MOCK_AVR_IO_H

#include <stdint.h>

extern volatile uint8_t DDRB;
extern volatile uint8_t DDRD;

extern volatile uint8_t PORTB;
extern volatile uint8_t PORTD;

#define PB5 5

#endif  // MOCK_AVR_IO_H
