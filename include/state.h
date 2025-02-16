#pragma once
#include "defs.h"
#include "flecs.h"

typedef struct State {
    ecs_world_t* world;
    Font font;
    u32 screenWidth;
    u32 screenHeight;
    v2* mouse;
    RenderTexture2D* screen;
} State;

extern State state;

void init_engine(const char* window_title);
