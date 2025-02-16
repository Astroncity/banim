#include "state.h"
#include "window.h"

State state = {0};
static bool is_init = false;

void init_engine(const char* window_title) {
    is_init = true;

    state.world = ecs_init();
    state.screenWidth = 640;
    state.screenHeight = 360;
    state.font = LoadFontEx("assets/fonts/spaceMono.ttf", 128, 0, 0);
    state.mouse = malloc(sizeof(v2));
    state.screen = init_window(window_title);
}
