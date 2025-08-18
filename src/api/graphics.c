/**
  src/api/graphics.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "graphics.h"

static RenderTexture2D graphics_framebuffer;
static size_t graphics_command_index = 0;
static draw_command_t graphics_commands[MAX_GRAPHICS_COMMANDS] = {0};

RenderTexture2D* graphics_init(void) {
  graphics_framebuffer = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
  return &graphics_framebuffer;
}

void graphics_push_command(draw_command_t cmd) {
  if (graphics_command_index == MAX_GRAPHICS_COMMANDS - 1)
    return;
  graphics_commands[graphics_command_index++] = cmd;
}

void graphics_clear(void) { graphics_push_command((draw_command_t){0}); }

void graphics_color(int color_id) {
  graphics_push_command((draw_command_t){1, (float)color_id, 0.0f});
}

void graphics_plot(float x, float y) {
  graphics_push_command((draw_command_t){2, x, y});
}

void graphics_move(float x, float y) {
  graphics_push_command((draw_command_t){3, x, y});
}

void graphics_draw(void) {
  static float turtle_x, turtle_y = 0.0f;
  static Color current_color;

  // Resize the framebuffer if needed.
  if (IsWindowResized()) {
    UnloadRenderTexture(graphics_framebuffer);
    graphics_framebuffer =
      LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
  }

  // Begin drawing.
  BeginTextureMode(graphics_framebuffer);

  for (int i = 0; i < graphics_command_index; i++) {
    draw_command_t current_command = graphics_commands[i];

    switch (current_command.id) {
    case 0: // Clear Background (graphics.clear())
      ClearBackground(BLACK);
      break;

    case 1: // Set Color (graphics.color())
      switch ((int)current_command.x) {
      default:
        current_color = WHITE;
        break;
      case 2:
        current_color = RED;
        break;
      case 3:
        current_color = ORANGE;
        break;
      case 4:
        current_color = YELLOW;
        break;
      case 5:
        current_color = GREEN;
        break;
      case 6:
        current_color = SKYBLUE;
        break;
      case 7:
        current_color = BLUE;
        break;
      case 8:
        current_color = PINK;
        break;
      }
      break;

    case 2: // Draw To Point (graphics.plot())
      // clang-format off
      DrawLineEx(
        (Vector2){
          turtle_x * GetRenderWidth(),
          turtle_y * GetRenderHeight()
        },
        (Vector2){
          current_command.x * GetRenderWidth(),
          current_command.y * GetRenderHeight()
        },
        3.0f,
        current_color
      );
      // clang-format on

    case 3: // Move To Point (graphics.move())
      turtle_x = current_command.x;
      turtle_y = current_command.y;
      break;

    default:
      break;
    }
  }

  graphics_command_index = 0;

  // End drawing and interrupt to draw framebuffer.
  EndTextureMode();
  runtime_interrupt();
}

size_t graphics_count(void) { return graphics_command_index; }

void graphics_free(void) { UnloadRenderTexture(graphics_framebuffer); }
