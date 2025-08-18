/**
  src/lualib/graphics.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "graphics.h"

static int luagraphics_clear(lua_State* L) {
  graphics_clear();
  return 0;
}

static int luagraphics_color(lua_State* L) {
  graphics_color(luaL_checkint(L, 1));
  return 0;
}

static int luagraphics_plot(lua_State* L) {
  graphics_plot((float)luaL_checknumber(L, 1), (float)luaL_checknumber(L, 2));
  return 0;
}

static int luagraphics_move(lua_State* L) {
  graphics_move((float)luaL_checknumber(L, 1), (float)luaL_checknumber(L, 2));
  return 0;
}

static int luagraphics_draw(lua_State* L) {
  graphics_draw();
  return 0;
}

/**
  Returns the result from `GetRenderWidth()`.
*/
static int luagraphics_width(lua_State* L) {
  lua_pushinteger(L, GetRenderWidth());
  return 1;
}

/**
  Returns the result from `GetRenderHeight()`.
*/
static int luagraphics_height(lua_State* L) {
  lua_pushinteger(L, GetRenderHeight());
  return 1;
}

/**
  Returns `GetRenderHeight() / GetRenderWidth()`.
*/
static int luagraphics_aspect(lua_State* L) {
  lua_pushnumber(L, (float)GetRenderHeight() / (float)GetRenderWidth());
  return 1;
}

/**
  Lua wrapper for `graphics_count()`.
*/
static int luagraphics_count(lua_State* L) {
  lua_pushinteger(L, graphics_count());
  return 1;
}

void luaopen_graphics(lua_State* L) {
  // clang-format off
  static const luaL_Reg luagraphics_lib[] = {
    {"clear", luagraphics_clear},
    {"color", luagraphics_color},
    {"plot", luagraphics_plot},
    {"move", luagraphics_move},
    {"draw", luagraphics_draw},
    {"width", luagraphics_width},
    {"height", luagraphics_height},
    {"aspect", luagraphics_aspect},
    {"count", luagraphics_count},
    {NULL, NULL}
  };
  // clang-format on

  luaL_register(L, "graphics", luagraphics_lib);
}
