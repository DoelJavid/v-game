#ifndef LUALIB_GRAPHICS_H
#define LUALIB_GRAPHICS_H

#include <lua.h>
#include <lauxlib.h>
#include <raylib.h>
#include "../runtime.h"

#define MAX_GRAPHICS_COMMANDS 255

typedef struct {
  int id;
  float x, y;
} draw_command_t;

/**
  Initializes the graphics library and returns a framebuffer.
*/
RenderTexture2D* graphics_init();

/**
  Pushes the given command to the draw commands if possible. If the total
  amount of commands is maxxed, then this function does nothing.
*/
void graphics_push_command(draw_command_t cmd);

/**
  Clears the screen of anything drawn and resets the current color to white.

  This function is meant to be called between Raylib's `BeginDrawing()` and
  `EndDrawing()`.
*/
void graphics_clear(void);

/**
  Sets the color to the given color index.

  There are 8 colors to choose from:
  1. White
  2. Red
  3. Orange
  3. Yellow
  4. Green
  5. Sky Blue
  6. Blue
  7. Pink
  8. Grey

  If the given color index is not valid, then white will be chosen by default.
*/
void graphics_color(int color_id);

/**
  Draws a line between the current graphics position and the given position,
  then moves the graphics position to the given position.

  This function is meant to be called between Raylib's `BeginDrawing()` and
  `EndDrawing()`.
*/
void graphics_plot(float x, float y);

/**
  Moves the draw position to the given position without drawing anything.
*/
void graphics_move(float x, float y);

/**
  Draws all the currently used commands.
*/
void graphics_draw();

/**
  Frees the current framebuffer.
*/
void graphics_free();

/**
  Opens the graphics library for the given lua state.
*/
void luaopen_graphics(lua_State* L);

#endif

