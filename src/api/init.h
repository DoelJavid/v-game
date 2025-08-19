/**
  src/api/init.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef API_INIT_H
#define API_INIT_H

#include "system.h"
#include "graphics.h"
#include "audio.h"
#include "input.h"

/**
  Initializes all APIs at once to be used.
*/
void api_init(sys_args_t args);

/**
  Stops all apis.
*/
void api_free(void);

#endif

