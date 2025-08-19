/**
  src/api/intro.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "intro.h"

void intro_play(void) {
  audio_blip(2, 15, 0.5, 0.1f); // Test to see if everything is working.

  for (int frame = 0; frame < 180; frame++) {
    graphics_clear();

    if (frame < 4) {
      graphics_color(1);

      for (float i = 0.1f; i < 1.0f; i += 0.1f) {
        graphics_move(i, 0.0f);
        graphics_plot(i, 1.0f);
      }

      for (float i = 0.1f; i < 1.0f; i += 0.1f) {
        graphics_move(0.0f, i);
        graphics_plot(1.0f, i);
      }
    } else {
      int color = frame > 90 ? 1 : frame / 3 % 8 + 1;

      // 'V'
      graphics_color(color);
      graphics_move(0.05, 0.6);
      graphics_plot(0.125, 0.45);
      graphics_plot(0.2, 0.6);
      graphics_plot(0.05, 0.6);
      color = color % 8 + 1;

      // '-'
      graphics_color(color);
      graphics_move(0.2, 0.5);
      graphics_plot(0.2825, 0.5);
      graphics_plot(0.2825, 0.535);
      graphics_plot(0.2, 0.535);
      graphics_plot(0.2, 0.5);
      color = color % 8 + 1;

      // 'G'
      graphics_color(color);
      graphics_move(0.45, 0.6);
      graphics_plot(0.3125, 0.6);
      graphics_plot(0.3125, 0.45);
      graphics_plot(0.45, 0.45);
      graphics_plot(0.45, 0.525);
      graphics_plot(0.4, 0.525);
      color = color % 8 + 1;

      // 'A'
      graphics_color(color);
      graphics_move(0.475, 0.45);
      graphics_plot(0.625, 0.45);
      graphics_plot(0.55, 0.6);
      graphics_plot(0.475, 0.45);
      color = color % 8 + 1;

      // 'M'
      graphics_color(color);
      graphics_move(0.65, 0.45);
      graphics_plot(0.8, 0.45);
      graphics_plot(0.8, 0.6);
      graphics_plot(0.725, 0.45);
      graphics_plot(0.65, 0.6);
      graphics_plot(0.65, 0.45);
      color = color % 8 + 1;

      // 'E'
      graphics_color(color);
      graphics_move(0.95, 0.45);
      graphics_plot(0.825, 0.45);
      graphics_plot(0.825, 0.525);
      graphics_plot(0.95, 0.525);
      graphics_move(0.825, 0.525);
      graphics_plot(0.825, 0.6);
      graphics_plot(0.95, 0.6);
      color = color % 8 + 1;
    }

    graphics_draw();
  }
}

