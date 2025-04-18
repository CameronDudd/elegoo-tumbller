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
void sendColorLEDReset();
void sendLEDColor(Color8 color);
void sendLEDColors(const Color8 *colors, const size_t numColors);
void flashLEDColors(const Color8 *colors, const size_t numColors, uint8_t numTimes);

#endif  // LED_H
