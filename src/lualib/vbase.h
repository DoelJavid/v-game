#ifndef LUALIB_VBASE_H
#define LUALIB_VBASE_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include "../runtime.h"

/**
  Opens the base library for V-GAME.
*/
void luaopen_vbase(lua_State* L);

#endif


