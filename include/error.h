/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef ERROR_H
#define ERROR_H

#include "led.h"

// Each module can have a unique colour to show the module the error occurred in
// 4 LEDs will allow 0b1111 (15) error states
// D1 - Back Right
// D2 - Back Left
// D3 - Front Left
// D4 - Front Right
typedef enum {
  NONE = 0,
  UNKNOWN = 1,
} ERROR_STATE;

void ledShowError(const Color moduleColor, const uint8_t statusCode);

#endif  // ERROR_H
