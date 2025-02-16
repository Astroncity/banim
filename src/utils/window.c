#include "window.h"
#include "state.h"

RenderTexture2D target = {0};

v2 v2Clamp(const v2 vec, const v2 min, const v2 max) {
    return (v2){MIN(MAX(vec.x, min.x), max.x), MIN(MAX(vec.y, min.y), max.y)};
}

static f32 get_window_scale() {
    return MIN((f32)GetScreenWidth() / state.screenWidth,
               (float)GetScreenHeight() / state.screenHeight);
    return MIN((f32)GetScreenWidth() / state.screenWidth,
               (float)GetScreenHeight() / state.screenHeight);
}

void update_mouse() {
    f32 scale = get_window_scale();
    v2 mOld = GetMousePosition();
    i32 sw = state.screenWidth;
    i32 sh = state.screenHeight;

    state.mouse->x = (mOld.x - (GetScreenWidth() - (sw * scale)) * 0.5f) / scale;
    state.mouse->y = (mOld.y - (GetScreenHeight() - (sh * scale)) * 0.5f) / scale;
    *state.mouse = v2Clamp(*state.mouse, (v2){0, 0}, (v2){(f32)sw, (f32)sh});
}

void draw_window() {
    BeginDrawing();
    ClearBackground(BLACK);
    f32 tw = (f32)target.texture.width;
    f32 th = (f32)target.texture.height;

    Rect rect1 = {0.0f, 0.0f, tw, -th};
    f32 scale = get_window_scale();

    i32 sw = state.screenWidth;
    i32 sh = state.screenHeight;

    f32 x = (GetScreenWidth() - (sw * scale)) * 0.5f;
    f32 y = (GetScreenHeight() - (sh * scale)) * 0.5f;

    Rect rect2 = {x, y, sw * scale, sh * scale};

    DrawTexturePro(target.texture, rect1, rect2, (v2){0, 0}, 0.0f, WHITE);
    EndDrawing();
}

RenderTexture2D* init_window(const char* title) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(state.screenWidth, state.screenHeight, title);
    InitAudioDevice();
    SetMasterVolume(1);
    SetTargetFPS(60);
    SetWindowSize(state.screenWidth, state.screenHeight);
    target = LoadRenderTexture(state.screenWidth, state.screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    return &target;
}
