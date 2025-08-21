/**
  src/lualib/vmath.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef LUALIB_VMATH_H
#define LUALIB_VMATH_H

#include <lua.h>
#include <lauxlib.h>
#include <math.h>

/*
  Opens the V-GAME math library for the given lua state. (Probably the longest
  library of functions in the runtime...)
*/
void luaopen_vmath(lua_State* L);

#endif

