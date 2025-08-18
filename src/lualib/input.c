/**
  src/lualib/input.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "input.h"

// clang-format off
static const char *const input_names[] = {
  "Start",
  "Select",

  "Up",
  "Right",
  "Down",
  "Left",

  "A",
  "B",
  "C",
  "D",

  "L",
  "R",
  NULL
};
// clang-format on

/**
  Lua version of input_pressed.

  This function can either take a number or an input name as an argument.
*/
static int luainput_pressed(lua_State* L) {
  int button_id = 0;
  if (lua_isnumber(L, 1)) {
    button_id = luaL_checkint(L, 1) - 1;
  } else {
    button_id = luaL_checkoption(L, 1, NULL, input_names);
  }

  lua_pushboolean(L, input_pressed(button_id, luaL_optint(L, 2, 1)));
  return 1;
}

/**
  Lua version of input_tapped.

  This function can either take a number or an input name as an argument.
*/
static int luainput_tapped(lua_State* L) {
  int button_id = 0;
  if (lua_isnumber(L, 1)) {
    button_id = luaL_checkint(L, 1) - 1;
  } else {
    button_id = luaL_checkoption(L, 1, NULL, input_names);
  }

  lua_pushboolean(L, input_tapped(button_id, luaL_optint(L, 2, 1)));
  return 1;
}

/**
  Grabs all the input from the controller and returns it as a table.

  The returned table is formatted like so:
  ```
  {
    Start: boolean,
    Select: boolean,

    Up: boolean,
    Right: boolean,
    Left: boolean,
    Down: boolean,

    A: boolean,
    B: boolean,
    C: boolean,
    D: boolean,

    L: boolean,
    R: boolean
  }
  ```

  By default this function will try to get input from controller one, but
  optionally a controller index can be given to specify which controller to
  read input from.
*/
static int luainput_grab(lua_State* L) {
  const int controller_id = luaL_optint(L, 1, 1);

  lua_createtable(L, 0, 12);
  for (int i = 0; i < 12; i++) {
    lua_pushboolean(L, input_pressed(i, controller_id));
    lua_setfield(L, -2, input_names[i]);
  }
  return 1;
}

void luaopen_input(lua_State* L) {
  // clang-format off
  static const luaL_Reg luainput_lib[] = {
    {"pressed", luainput_pressed},
    {"tapped", luainput_tapped},
    {"grab", luainput_grab},
    {NULL, NULL}
  };
  //clang-format on

  luaL_register(L, "input", luainput_lib);
}
