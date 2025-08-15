#include "runtime.h"

static lua_State* L;
static RenderTexture runtime_framebuffer;

int runtime_init(runtime_args_t args) {

  // Initialize game window.
  SetTraceLogLevel(LOG_NONE);
  InitWindow(800, 600, "V-Game");
  SetTargetFPS(60);

  runtime_framebuffer = graphics_init();

  // Initialize Lua runtime.
  lua_State* L = luaL_newstate();
  if (!L) {
    return 99;
  }

  luaopen_vbase(L);
  luaopen_graphics(L);
  luaopen_input(L);
  luaopen_math(L);
  luaopen_string(L);

  // Remove string.dump.
  lua_getglobal(L, "string");
  lua_pushnil(L);
  lua_setfield(L, -2, "dump");
  lua_pop(L, 1);

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
  if (WindowShouldClose()) {
    if (L)
      lua_close(L);

    CloseWindow();
    exit(0);
  }
}

void runtime_interrupt() {
  runtime_check_close();
  BeginDrawing();
  DrawTexture(runtime_framebuffer.texture, 0, 0, WHITE);
  EndDrawing();
}

void runtime_panic(const char* msg) {
  printf("ERROR: %s\n", msg);
  if (GetWindowHandle())
    CloseWindow();

  graphics_free();
  exit(1);
}

