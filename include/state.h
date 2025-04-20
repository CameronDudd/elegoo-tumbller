/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef STATE_H
#define STATE_H

#define NUM_STATES 2

typedef enum {
  STDBY   = 0,
  BALANCE = 1,
} State;

extern State state;

#endif  // STATE_H
