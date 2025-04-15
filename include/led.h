/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef LED_H
#define LED_H

#include <stddef.h>

#include "color.h"
#include "stdint.h"

void initLED();
void toggleOnBoardLED();
void colorReset();
void sendColor(Color8 color);
void sendColors(const Color8 *colors, const size_t numColors);
void flashColors(const Color8 *colors, const size_t numColors, uint8_t numTimes);

#endif  // LED_H
