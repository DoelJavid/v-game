/**
  src/api/input.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "input.h"

// clang-format off
static const int keyboard_input_map[] = {
    KEY_ENTER, KEY_SPACE,

    KEY_UP,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_LEFT,

    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,

    KEY_A,
    KEY_D
};

static const int gamepad_input_map[] = {
  GAMEPAD_BUTTON_MIDDLE_RIGHT,
  GAMEPAD_BUTTON_MIDDLE_LEFT,

  GAMEPAD_BUTTON_LEFT_FACE_UP,
  GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
  GAMEPAD_BUTTON_LEFT_FACE_DOWN,
  GAMEPAD_BUTTON_LEFT_FACE_LEFT,

  GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
  GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
  GAMEPAD_BUTTON_RIGHT_FACE_UP,
  GAMEPAD_BUTTON_RIGHT_FACE_LEFT,

  GAMEPAD_BUTTON_LEFT_TRIGGER_1,
  GAMEPAD_BUTTON_RIGHT_TRIGGER_1
};
// clang-format on

bool input_pressed(int button_id, int controller_id) {
  if (button_id < 0 || button_id > 12)
    return false;

  return IsGamepadButtonDown(0, gamepad_input_map[button_id]) ||
         IsKeyDown(keyboard_input_map[button_id]);
}

bool input_tapped(int button_id, int controller_id) {
  if (button_id < 0 || button_id > 12)
    return false;

  return IsGamepadButtonPressed(0, gamepad_input_map[button_id]) ||
         IsKeyPressed(keyboard_input_map[button_id]);
}
