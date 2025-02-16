#include "flecs.h"
#include "render.h"
#include "state.h"
#include "transform.h"
#include "window.h"
#include <raylib.h>
#include <stdio.h>

void init_latex(const char* to_replace) {
    FILE *sed_output, *tectonic_input;
    char buffer[1024];
    char sed_command[1024];

    snprintf(sed_command, sizeof(sed_command),
             "sed 's/<BEGIN_REPLACE>/%s/g' test.tex", to_replace);

    sed_output = popen(sed_command, "r");
    tectonic_input = popen("tectonic -", "w");

    while (fgets(buffer, sizeof(buffer), sed_output) != NULL) {
        fputs(buffer, tectonic_input);
    }

    pclose(sed_output);
    pclose(tectonic_input);

    system("magick -density 600 texput.pdf -quality 100 testAuto.png");
}

void cleanup_latex() {
    system("rm testAuto.png");
    system("rm texput.pdf");
    system("rm test.aux");
    system("rm test.log");
}

int main(void) {
    init_engine("Banim");

    ECS_IMPORT(state.world, Transform);
    ECS_IMPORT(state.world, Renderer);

    init_latex("\\\\alpha^2+ b^2 = c^2");
    Texture2D tex = LoadTexture("testAuto.png");

    while (!WindowShouldClose()) {
        update_mouse();

        BeginTextureMode(*state.screen);
        ClearBackground(BLACK);

        DrawTextureEx(tex, (v2){0, 0}, 0, 1.5, WHITE);

        ecs_progress(state.world, GetFrameTime());

        EndTextureMode();
        draw_window();
    }

    cleanup_latex();
    CloseWindow();
    return 0;
}
