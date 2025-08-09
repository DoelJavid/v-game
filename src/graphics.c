#include "graphics.h"

static float turtle_x = 0.0;
static float turtle_y = 0.0;
static Color current_color;

// C API

void graphics_color(int color_id) {
  switch (color_id) {
  default:
    current_color = WHITE;
    return;
  case 2:
    current_color = RED;
    return;
  case 3:
    current_color = ORANGE;
    return;
  case 4:
    current_color = YELLOW;
    return;
  case 5:
    current_color = GREEN;
    return;
  case 6:
    current_color = SKYBLUE;
    return;
  case 7:
    current_color = BLUE;
    return;
  case 8:
    current_color = PINK;
    return;
  }
}

void graphics_move(float x, float y) {
  turtle_x = x;
  turtle_y = y;
}

void graphics_plot(float x, float y) {
  DrawLineEx(
    (Vector2){turtle_x * GetScreenWidth(), turtle_y * GetScreenHeight()},
    (Vector2){x * GetScreenWidth(), y * GetScreenHeight()},
    3.0f, WHITE
  );
  graphics_move(x, y);
}

void graphics_clear(void) {
  ClearBackground(BLACK);
  graphics_color(1);
}

