/**
  src/lualib/audio.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "audio.h"

static int luaaudio_blip(lua_State* L) {
  int channel = luaL_checkint(L, 1);

  luaL_checktype(L, 2, LUA_TTABLE);
  lua_getfield(L, 2, "Semitone");
  lua_getfield(L, 2, "Volume");
  lua_getfield(L, 2, "Duration");

  int semitone = luaL_optint(L, -3, 3);
  float volume = luaL_optnumber(L, -2, 0.5f);
  float duration = luaL_optnumber(L, -1, 0.2f);

  lua_pop(L, 3);
  audio_blip(channel, semitone, volume, duration);
  return 0;
}

void luaopen_audio(lua_State* L) {
  // clang-format off
  static const luaL_Reg luaaudio_lib[] = {
    {"blip", luaaudio_blip},
    {NULL, NULL}
  };
  // clang-format on

  luaL_register(L, "audio", luaaudio_lib);
}
