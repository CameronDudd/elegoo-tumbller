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

typedef struct {
  float KP;
  float KI;
  float KD;
} PIDConstants;

extern State state;
extern PIDConstants pitchPIDConstants;

#endif  // STATE_H
