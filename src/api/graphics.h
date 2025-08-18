/**
  src/api/graphics.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef API_GRAPHICS_H
#define API_GRAPHICS_H

#include "../runtime.h"
#include <raylib.h>

#define MAX_GRAPHICS_COMMANDS 255

typedef struct {
  int id;
  float x, y;
} draw_command_t;

/**
  Initializes the graphics library and returns a framebuffer.
*/
RenderTexture2D* graphics_init(void);

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
  4. Yellow
  5. Green
  6. Light Blue
  7. Blue
  8. Pink

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
void graphics_draw(void);

/**
  Gets the total amount of commands stored within graphics memory.
*/
const size_t graphics_count(void);

/**
  Frees the current framebuffer.
*/
void graphics_free(void);

#endif
