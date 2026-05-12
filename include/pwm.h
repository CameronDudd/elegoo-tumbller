/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#ifndef PWM_H
#define PWM_H

#include <stdint.h>

void pwmInit(void);
void pwmSet(uint8_t channel, uint8_t duty);
void pwmStopAll(void);

#endif
