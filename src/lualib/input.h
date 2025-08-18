/**
  src/lualib/input.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef LUALIB_INPUT_H
#define LUALIB_INPUT_H

#include "../api/input.h"
#include <lauxlib.h>
#include <lua.h>

/**
  Activates the input library within the given lua state.
*/
void luaopen_input(lua_State* L);

#endif
