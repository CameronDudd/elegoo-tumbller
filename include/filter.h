/*
 *   Copyright (c) 2026 Cameron Dudd
 *   All rights reserved.
 */

#ifndef FILTER_H
#define FILTER_H

typedef struct {  // Complimentary filter
  float alpha;
  float dt;
  float estimate;
} CompFilter;

void initCompFilter(CompFilter* f, float alpha, float dt, float initialValue);
float updateCompFilter(CompFilter* f, float lowPassSignal, float highPassRate);

#endif  // FILTER_H
