#pragma once

#include "defs.h"

#define MAG(v) sqrt(v.x* v.x + v.y * v.y)

void update_mouse(void);
void draw_window(void);
v2 v2Clamp(const v2 vec, const v2 min, const v2 max);
RenderTexture2D* init_window(const char* title);
