#include "system.h"

/**
  Prints all data passed from Lua to the console.
*/
static int luasystem_log(lua_State* L) {
  int nargs = lua_gettop(L);
  for (int i = 1; i <= nargs; i++) {
    lua_pushcfunction(L, luavbase_tostring);
    lua_pushvalue(L, i);
    lua_call(L, 1, 1);
    SYSTEM_LOG(lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  return 0;
}

/**
  Prints all data passed from Lua to the console formatted as a warning.
*/
static int luasystem_warn(lua_State* L) {
  int nargs = lua_gettop(L);
  for (int i = 1; i <= nargs; i++) {
    lua_pushcfunction(L, luavbase_tostring);
    lua_pushvalue(L, i);
    lua_call(L, 1, 1);
    SYSTEM_WARN_LOG(lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  return 0;
}

/**
  Prints all data passed from Lua to the console formatted as an error message.
*/
static int luasystem_error(lua_State* L) {
  int nargs = lua_gettop(L);
  for (int i = 1; i <= nargs; i++) {
    lua_pushcfunction(L, luavbase_tostring);
    lua_pushvalue(L, i);
    lua_call(L, 1, 1);
    SYSTEM_ERROR_LOG(lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  return 0;
}

/**
  Throws a fatal error and kills the application as long as it's not caught by
  `pcall`.
*/
static int luasystem_panic(lua_State* L) {
  lua_pushcfunction(L, luavbase_tostring);
  lua_pushvalue(L, 1);
  lua_call(L, 1, 1);
  const char* msg = lua_tostring(L, -1);
  lua_pop(L, 1);
  return luaL_error(L, msg);
}

/**
  Exits the program with the given exit code.
*/
static int luasystem_exit(lua_State* L) {
  exit(luaL_optint(L, 1, 0));
  return 0;
}

/**
  Returns the current tick of the application (how many interrupts have been
  called).
*/
static int luasystem_tick(lua_State* L) {
  lua_pushinteger(L, system_tick());
  return 1;
}

/**
  Returns the current time in the form of a unix timestamp.
*/
static int luasystem_time(lua_State* L) {
  lua_pushinteger(L, SYSTEM_GET_TIME());
  return 1;
}

void luaopen_system(lua_State* L) {
  static const luaL_Reg luasystem_lib[] = {
    {"log", luasystem_log},
    {"warn", luasystem_warn},
    {"error", luasystem_error},
    {"panic", luasystem_panic},
    {"exit", luasystem_exit},
    {"tick", luasystem_tick},
    {"time", luasystem_time},
    {NULL, NULL}
  };

  luaL_register(L, "system", luasystem_lib);
}

