

#ifndef LUALIB_SYSTEM_H
#define LUALIB_SYSTEM_H

#include "../api/system.h"
#include <lua.h>
#include <lauxlib.h>

/**
  Activates the `system` library within the given lua state.
*/
void luaopen_system(lua_State* L);

#endif

