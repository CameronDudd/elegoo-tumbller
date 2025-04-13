/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef LED_H
#define LED_H

#include <stddef.h>

#include "stdint.h"

#define HEX_LED_OFF 0x00
#define HEX_LED_MAX 0x3F

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

extern const Color COLOR_LED_OFF;
extern const Color COLOR_LED_WHITE;
extern const Color COLOR_LED_RED;
extern const Color COLOR_LED_GREEN;
extern const Color COLOR_LED_BLUE;
extern const Color COLOR_LED_BECKS;

void initLED();
void toggleOnBoardLED();
void colorReset();
void sendColor(Color color);
void sendColors(const Color *colors, size_t numColors);

#endif  // LED_H
