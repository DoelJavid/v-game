/**
  src/lualib/init.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef LUALIB_INIT_H
#define LUALIB_INIT_H

#include "vbase.h"
#include "system.h"
#include "input.h"
#include "graphics.h"
#include "audio.h"
#include <lua.h>
#include <lauxlib.h>
#include <string.h>

/**
  Initializes all libraries within the given lua state.
*/
void vlua_openlibs(lua_State* L);

/**
  Starts the game at the given path.
*/
int vlua_init(const char* path);

/**
  Frees Lua, effectively stopping the runtime. This function can be used within
  a signal handler or `atexit()` listener to handle resource clean up.
*/
void vlua_free(void);

#endif

