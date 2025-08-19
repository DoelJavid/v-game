/**
  src/api/init.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "init.h"

void api_init(sys_args_t args) {
  system_init(args);
  graphics_init(system_get_framebuffer());
  audio_init();
}

void api_free(void) {
  audio_free();
  graphics_free();
  system_free();
}

