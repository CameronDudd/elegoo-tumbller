/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#include "command.h"

#include <string.h>

#define CMD_FIFO_SIZE 8

static Command cmdFifo[CMD_FIFO_SIZE];
static Command* rPtr       = cmdFifo;
static Command* wPtr       = cmdFifo;
static Command* cmdFifoEnd = cmdFifo + CMD_FIFO_SIZE;

static Command* stepPtr(Command* ptr) {
  ++ptr;
  if (ptr >= cmdFifoEnd) {
    ptr = cmdFifo;
  }
  return ptr;
}

static void copyCmd(Command* to, const Command* from) {
  to->type = from->type;

  strncpy(to->key, from->key, KEY_SIZE - 1);
  to->key[KEY_SIZE - 1] = '\0';

  to->value = from->value;
  to->ready = from->ready;
}

bool popCmd(Command* cmd) {
  if (rPtr == wPtr) {
    return false;
  }
  copyCmd(cmd, rPtr);
  rPtr = stepPtr(rPtr);
  return true;
}

void pushCmd(const Command* cmd) {
  Command* n = stepPtr(wPtr);
  if (n == rPtr) {
    rPtr = stepPtr(rPtr);
  }
  copyCmd(wPtr, cmd);
  wPtr = n;
}
