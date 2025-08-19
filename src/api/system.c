/**
  src/api/system.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "system.h"

static RenderTexture2D system_framebuffer;
static size_t current_tick = 0;

const size_t system_tick(void) {
  return current_tick;
}

RenderTexture2D* system_get_framebuffer(void) {
  return &system_framebuffer;
}

int system_init(sys_args_t args) {
  // Initialize game window.
  SetTraceLogLevel(LOG_NONE);
  InitWindow(800, 600, "V-Game");
  SetTargetFPS(60);
  SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

  if (args.fullscreen) {
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    ToggleFullscreen();
  }

  return 0;
}

void system_interrupt(void) {
  if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
    system_free();
    exit(0);
  } else {
    BeginDrawing();
    DrawTexture(system_framebuffer.texture, 0, 0, WHITE);
    EndDrawing();

    if (IsWindowResized()) {
      UnloadRenderTexture(system_framebuffer);
      system_framebuffer =
        LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
    }

    current_tick++;
  }
}

void system_free(void) {
  if (IsRenderTextureValid(system_framebuffer))
    UnloadRenderTexture(system_framebuffer);

  if (IsWindowReady()) {
    CloseWindow();
  }
}
