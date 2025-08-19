/**
  src/lualib/vbase.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "vbase.h"

/**
  Returns the type of the given value in the form of a string. Unlike the
  traditional `type()` function, this function supports a special case for
  tables that have a `__type` field, where it will return `table.__type` if
  it's a string.
*/
static int luavbase_type(lua_State* L) {
  luaL_checkany(L, 1);

  if (lua_type(L, 1) == LUA_TTABLE) {
    lua_pushstring(L, "__type");
    lua_rawget(L, 1);

    int custom_table_type = lua_type(L, -1);
    if (custom_table_type == LUA_TSTRING) {
      return 1;
    } else if (custom_table_type != LUA_TNIL) {
      return luaL_error(L, "Invalid table type!");
    }
  }

  lua_pushstring(L, luaL_typename(L, 1));
  return 1;
}

/**
  Sleeps for the given amount of frames.
*/
static int luavbase_sleep(lua_State* L) {
  for (int frames = luaL_checkint(L, 1); frames > 0; frames--)
    system_interrupt();
  return 0;
}

void luaopen_vbase(lua_State* L) {
  // clang-format off
  static const luaL_Reg luavbase_lib[] = {
    {"sleep", luavbase_sleep},
    {"type", luavbase_type}, {NULL, NULL}
  };

  static const char* unsafe_base_globals[] = {
    "dofile",
    "getfenv",
    "load",
    "loadfile",
    "loadstring",
    "module",
    "rawequal",
    "rawget",
    "rawset",
    "require",
    "setfenv",
    "getmetatable",
    "setmetatable",
    "type",
    "print",
    "error",
    "select"
  };
  // clang-format on

  // Load lua's base functions.
  luaopen_base(L);

  // Override unsafe Lua functions.
  for (int i = sizeof(unsafe_base_globals) / sizeof(const char*) - 1; i >= 0;
       i--) {
    lua_pushnil(L);
    lua_setglobal(L, unsafe_base_globals[i]);
  }

  // Define V-GAME-specific base functions.
  // For compatibility with vanilla Lua 5.1.
  for (const luaL_Reg* reg = &luavbase_lib[0];
       reg->name != NULL && reg->func != NULL; reg++) {
    lua_register(L, reg->name, reg->func);
  }
}

