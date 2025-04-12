/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef LED_H
#define LED_H

#include "stdint.h"

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

void initLED();
void toggleOnBoardLED();
void colorReset();
void sendColor(Color *color);

#endif  // LED_H
