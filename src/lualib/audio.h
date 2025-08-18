/**
  src/lualib/audio.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef LUALIB_AUDIO_H
#define LUALIB_AUDIO_H

#include "../api/audio.h"
#include <lauxlib.h>
#include <lua.h>

/**
  Opens the audio library for the given lua state.
*/
void luaopen_audio(lua_State* L);

#endif
