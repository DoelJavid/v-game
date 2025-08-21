/**
  src/lualib/vbase.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef LUALIB_VBASE_H
#define LUALIB_VBASE_H

#include "../api/system.h"
#include "audio.h"
#include "graphics.h"
#include "input.h"
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>
#include <string.h>

/**
  Attempts to convert the given Lua value to a string.

  If the given value is a table, it will first attempt to return the result of
  the table  method `__tostring`. If the `__tostring field doesn't exist, it
  will return a string representation of the given table.

  If the given value is a function, the given function will be called with no
  arguments and the return value will be returned as a string.
*/
int luavbase_tostring(lua_State* L);

/**
  Opens the base library for V-GAME.
*/
void luaopen_vbase(lua_State* L);

#endif

