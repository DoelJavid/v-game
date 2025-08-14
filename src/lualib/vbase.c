#include "vbase.h"

// A good chunk of this is copied from `lbaselib.c` except for `lua_sleep`.

/**
  Sleeps for the given amount of frames.
*/
static int lua_sleep(lua_State* L) {
  for (int frames = luaL_checkint(L, 1); frames > 0; frames--) {
    runtime_interrupt();
  }
  return 0;
}

void luaopen_vbase(lua_State* L) {
  static const luaL_Reg lua_lib[] = {
    {"sleep", lua_sleep},
    {NULL, NULL}
  };

  static const char* unsafe_base_globals[] = {
    "dofile",
    "getfenv",
    "load",
    "loadfile",
    "loadstring",
    "module",
    "require",
    "setfenv"
  };

  // Load lua's base functions.
  luaopen_base(L);

  // Override unsafe Lua functions.
  for (
    int i = sizeof(unsafe_base_globals) / sizeof(const char*) - 1;
    i >= 0;
    i--
  ) {
    lua_pushnil(L);
    lua_setglobal(L, unsafe_base_globals[i]);
  }

  // Define V-GAME-specific base functions.
  // For compatibility with vanilla Lua 5.1.
  for (
    luaL_Reg* reg = &lua_lib[0];
    reg->name != NULL && reg->func != NULL;
    reg++
  ) {
    lua_register(L, reg->name, reg->func);
  }
  luaL_register(L, NULL, lua_lib);
}

