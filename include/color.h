/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// Color 8 (bits per channel) maximum 255
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color8;

extern const Color8 COLOR_OFF;
extern const Color8 COLOR_WHITE;
extern const Color8 COLOR_RED;
extern const Color8 COLOR_GREEN;
extern const Color8 COLOR_BLUE;

#endif  // COLOR_H
