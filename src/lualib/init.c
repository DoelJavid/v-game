/**
  src/lualib/init.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "init.h"

static lua_State* L;

void vlua_openlibs(lua_State* L) {
  luaopen_vbase(L);
  luaopen_graphics(L);
  luaopen_audio(L);
  luaopen_input(L);
  luaopen_system(L);
  luaopen_math(L);
  luaopen_string(L);

  // Remove string.dump.
  lua_getglobal(L, "string");
  lua_pushnil(L);
  lua_setfield(L, -2, "dump");
  lua_pop(L, 1);
}

int vlua_init(const char* path) {
  if (!(L = luaL_newstate()))
    return 1;
  vlua_openlibs(L);

  if (luaL_dofile(L, path)) {
    const char* error = lua_tostring(L, -1);
    char message[512];
    strncpy(message, error, 512);

    SYSTEM_PANIC_LOG("%s", message);

    if (L) {
      lua_close(L);
      L = NULL;
    }
    return 1;
  }

  lua_close(L);
  return 0;
}

void vlua_free(void) {
  if (L) {
    lua_close(L);
    L = NULL;
  }
}

