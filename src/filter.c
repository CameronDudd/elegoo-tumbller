/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "filter.h"

void initCompFilter(CompFilter* f, float alpha, float dt, float initialValue) {
  f->alpha    = alpha;
  f->dt       = dt;
  f->estimate = initialValue;
}

float updateCompFilter(CompFilter* f, float lowPassSignal, float highPassRate) {
  float highPassComponent = f->estimate + (highPassRate * f->dt);
  f->estimate             = (f->alpha * highPassComponent) + ((1.0f - f->alpha) * lowPassSignal);
  return f->estimate;
}
