#include "graphics.h"

static RenderTexture2D graphics_framebuffer;
static size_t graphics_command_index = 0;
static draw_command_t graphics_commands[MAX_GRAPHICS_COMMANDS] = {0};

// C API

RenderTexture2D* graphics_init() {
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

void graphics_draw() {
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
      DrawLineEx(
        (Vector2){turtle_x * GetRenderWidth(), turtle_y * GetRenderHeight()},
        (Vector2){current_command.x * GetRenderWidth(),
                  current_command.y * GetRenderHeight()},
        3.0f, current_color
      );

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

void graphics_free() { UnloadRenderTexture(graphics_framebuffer); }

// Lua API

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
    {NULL, NULL}
  };
  // clang-format on

  luaL_register(L, "graphics", luagraphics_lib);
}
