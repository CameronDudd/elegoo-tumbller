/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "color.h"

#define HEX_OFF 0x00
#define HEX_MAX 0x3F

const Color8 COLOR_OFF = {
    .r = HEX_OFF,
    .g = HEX_OFF,
    .b = HEX_OFF,
};
const Color8 COLOR_WHITE = {
    .r = HEX_MAX,
    .g = HEX_MAX,
    .b = HEX_MAX,
};
const Color8 COLOR_RED = {
    .r = HEX_MAX,
    .g = HEX_OFF,
    .b = HEX_OFF,
};
const Color8 COLOR_GREEN = {
    .r = HEX_OFF,
    .g = HEX_MAX,
    .b = HEX_OFF,
};
const Color8 COLOR_BLUE = {
    .r = HEX_OFF,
    .g = HEX_OFF,
    .b = HEX_MAX,
};
