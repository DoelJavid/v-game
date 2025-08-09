#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <raylib.h>

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
  Moves the draw position to the given position without drawing anything.
*/
void graphics_move(float x, float y);

/**
  Draws a line between the current graphics position and the given position,
  then moves the graphics position to the given position.

  This function is meant to be called between Raylib's `BeginDrawing()` and
  `EndDrawing()`.
*/
void graphics_plot(float x, float y);

/**
  Clears the screen of anything drawn and resets the current color to white.

  This function is meant to be called between Raylib's `BeginDrawing()` and
  `EndDrawing()`.
*/
void graphics_clear(void);

#endif

