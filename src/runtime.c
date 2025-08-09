#include "runtime.h"

/**
  Private function that manages graphics state.
*/
static void runtime_draw(void) {
  BeginDrawing();

  graphics_clear();

  graphics_move(0.25f, 0.75f);
  graphics_plot(0.5f, 0.25f);
  graphics_plot(0.75f, 0.75f);
  graphics_plot(0.25f, 0.75f);

  EndDrawing();
}

int runtime_init(void) {
  // Initialize game window.
  InitWindow(800, 600, "V-Game");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    runtime_draw();
  }

  CloseWindow();

  return 0;
}

