/**
  src/lualib/vstring.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef LUALIB_VSTRING_H
#define LUALIB_VSTRING_H

#include <ctype.h>
#include <lua.h>
#include <lauxlib.h>

/*
  Opens the V-GAME string library for the given lua state.
*/
void luaopen_vstring(lua_State* L);

#endif

