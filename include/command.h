/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "stdbool.h"

#define KEY_SIZE 16

typedef enum {
  NUL,
  GET,
  SET,
} CommandT;

typedef struct {
  CommandT type;
  char key[KEY_SIZE];
  float value;
  bool ready;
} Command;

bool popCmd(Command* cmd);
void pushCmd(const Command* cmd);

#endif  // COMMAND_H
