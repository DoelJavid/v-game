#include "runtime.h"

static lua_State* L;
static RenderTexture2D* runtime_framebuffer;

/**
  Draws the intro at the given frame.
*/
static void runtime_draw_intro(int frame) {
  graphics_clear();

  if (frame < 4) {
    graphics_color(1);

    for (float i = 0.1f; i < 1.0f; i += 0.1f) {
      graphics_move(i, 0.0f);
      graphics_plot(i, 1.0f);
    }

    for (float i = 0.1f; i < 1.0f; i += 0.1f) {
      graphics_move(0.0f, i);
      graphics_plot(1.0f, i);
    }
  } else {
    int color = frame > 90 ? 1 : frame / 3 % 8 + 1;

    // 'V'
    graphics_color(color);
    graphics_move(0.05, 0.6);
    graphics_plot(0.125, 0.45);
    graphics_plot(0.2, 0.6);
    graphics_plot(0.05, 0.6);
    color = color % 8 + 1;

    // '-'
    graphics_color(color);
    graphics_move(0.2, 0.5);
    graphics_plot(0.2825, 0.5);
    graphics_plot(0.2825, 0.535);
    graphics_plot(0.2, 0.535);
    graphics_plot(0.2, 0.5);
    color = color % 8 + 1;

    // 'G'
    graphics_color(color);
    graphics_move(0.45, 0.6);
    graphics_plot(0.3125, 0.6);
    graphics_plot(0.3125, 0.45);
    graphics_plot(0.45, 0.45);
    graphics_plot(0.45, 0.525);
    graphics_plot(0.4, 0.525);
    color = color % 8 + 1;

    // 'A'
    graphics_color(color);
    graphics_move(0.475, 0.45);
    graphics_plot(0.625, 0.45);
    graphics_plot(0.55, 0.6);
    graphics_plot(0.475, 0.45);
    color = color % 8 + 1;

    // 'M'
    graphics_color(color);
    graphics_move(0.65, 0.45);
    graphics_plot(0.8, 0.45);
    graphics_plot(0.8, 0.6);
    graphics_plot(0.725, 0.45);
    graphics_plot(0.65, 0.6);
    graphics_plot(0.65, 0.45);
    color = color % 8 + 1;

    // 'E'
    graphics_color(color);
    graphics_move(0.95, 0.45);
    graphics_plot(0.825, 0.45);
    graphics_plot(0.825, 0.525);
    graphics_plot(0.95, 0.525);
    graphics_move(0.825, 0.525);
    graphics_plot(0.825, 0.6);
    graphics_plot(0.95, 0.6);
    color = color % 8 + 1;
  }

  graphics_draw();
}

int runtime_init(runtime_args_t args) {

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

  runtime_framebuffer = graphics_init();
  audio_init();

  // Initialize Lua runtime.
  lua_State* L = luaL_newstate();
  if (!L) {
    return 99;
  }

  luaopen_vbase(L);
  luaopen_graphics(L);
  luaopen_audio(L);
  luaopen_input(L);
  luaopen_math(L);
  luaopen_string(L);

  // Remove string.dump.
  lua_getglobal(L, "string");
  lua_pushnil(L);
  lua_setfield(L, -2, "dump");
  lua_pop(L, 1);

  if (!args.cut_intro) {
    // Play the intro.
    audio_blip(2, 15, 0.5, 0.1f); // Test to see if everything is working.
    for (int frame = 0; frame < 180; frame++)
      runtime_draw_intro(frame);
  }

  printf("Executing game at %s\n", args.starting_game);
  if (luaL_dofile(L, args.starting_game)) {
    const char* error = lua_tostring(L, -1);
    char msg[512];
    strncpy(msg, error, 512);
    lua_close(L);
    runtime_panic(msg);
  }

  lua_close(L);
  CloseWindow();

  return 0;
}

void runtime_check_close() {
  if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
    if (L)
      lua_close(L);

    graphics_free();
    audio_free();
    CloseWindow();
    exit(0);
  }
}

void runtime_interrupt() {
  runtime_check_close();
  BeginDrawing();
  DrawTexture(runtime_framebuffer->texture, 0, 0, WHITE);
  EndDrawing();
}

void runtime_panic(const char* msg) {
  printf("ERROR: %s\n", msg);
  if (GetWindowHandle())
    CloseWindow();

  graphics_free();
  audio_free();
  exit(1);
}
