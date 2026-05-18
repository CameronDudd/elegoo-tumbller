/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#ifndef ELEGOOKIT_H
#define ELEGOOKIT_H

typedef enum {
  MOVE_FORWARD    = 'f',
  MOVE_BACKWARD   = 'b',
  MOVE_LEFT       = 'l',
  MOVE_RIGHT      = 'i',
  MOVE_STOP       = 's',
  MODE_COMPLIANCE = '0',  // Move with push,
  MODE_FIGHT      = '1',  // Move against push,
  MODE_FREE       = '2',  // Wall sensing,
  TOGGLE_LIGHTS   = '3',
  BALANCE_STOP    = '4',
  BALANCE_START   = '5',
  DECREASE_LIGHTS = '7',
  INCREASE_LIGHTS = '8',
} ElegooKitCommand;

#endif  // ELEGOOKIT_H
