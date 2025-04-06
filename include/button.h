/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef BUTTON_H
#define BUTTON_H

#define NUM_STATES 2

typedef enum {
  STDBY = 0,
  BALANCE = 1,
} State;

extern State state;

void initButtons();

#endif  // BUTTON_H
