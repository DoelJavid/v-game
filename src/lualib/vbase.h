#ifndef LUALIB_VBASE_H
#define LUALIB_VBASE_H

#include "../runtime.h"
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>

/**
  Opens the base library for V-GAME.
*/
void luaopen_vbase(lua_State *L);

#endif
