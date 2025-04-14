/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "state.h"

void ledShowError(const Color moduleColor, const uint8_t statusCode) {
  const Color colors[4] = {
      (statusCode & (1 << 0)) ? moduleColor : COLOR_LED_OFF,
      (statusCode & (1 << 1)) ? moduleColor : COLOR_LED_OFF,
      (statusCode & (1 << 2)) ? moduleColor : COLOR_LED_OFF,
      (statusCode & (1 << 3)) ? moduleColor : COLOR_LED_OFF,
  };
  sendColors(colors, 4);
}
