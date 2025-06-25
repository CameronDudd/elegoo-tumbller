/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "state.h"

State state = BALANCE;

PIDConstants pitchPIDConstants = {
    .KP = 5.0,
    .KI = 0.0,
    .KD = 0.0,
};
