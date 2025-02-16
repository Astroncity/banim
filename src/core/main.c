#include "flecs.h"
#include "render.h"
#include "state.h"
#include "transform.h"
#include "window.h"
#include <raylib.h>
#include <stdio.h>

void draw_splash(void) {
    const char* splash_text = "Hello Engine!";
    v2 len = MeasureTextEx(GetFontDefault(), splash_text, 20, 1);

    Vector2 position = {state.screenWidth / 2 - len.x / 2,
                        state.screenHeight / 2 - len.y / 2};
    DrawTextEx(GetFontDefault(), splash_text, position, 20, 1, WHITE);
}

int main(void) {
    init_engine("Engine Template");

    ECS_IMPORT(state.world, Transform);
    ECS_IMPORT(state.world, Renderer);

    while (!WindowShouldClose()) {
        update_mouse();

        BeginTextureMode(*state.screen);
        ClearBackground(BLACK);

        draw_splash();
        ecs_progress(state.world, GetFrameTime());

        EndTextureMode();
        draw_window();
    }

    CloseWindow();
    return 0;
}
