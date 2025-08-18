/**
  src/lualib/graphics.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef LUALIB_GRAPHICS_H
#define LUALIB_GRAPHICS_H

#include "../api/graphics.h"
#include <lauxlib.h>
#include <lua.h>

/**
  Opens the graphics library for the given lua state.
*/
void luaopen_graphics(lua_State* L);

#endif
