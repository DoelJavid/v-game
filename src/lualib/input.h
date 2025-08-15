#ifndef LUALIB_INPUT_H
#define LUALIB_INPUT_H

#include <lua.h>
#include <lauxlib.h>
#include <raylib.h>

/**
  Returns true if the given button index is pressed and false if otherwise.

  By default this function will try to get input from controller one, but
  optionally a controller index can be given to specify which controller to
  read input from.

  Input Codes:
  1: Start
  2: Select
  3: D-pad Up
  4: D-pad Right
  5: D-pad Down
  6: D-pad Left
  7: A
  8: B
  9: C
  10: D
  11: L
  12: R
*/
bool input_button(int button_id, int controller_id);

/**
  Activates the input library within the given lua state.
*/
void luaopen_input(lua_State* L);

#endif
