/**
  src/api/system.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#ifndef API_SYSTEM_H
#define API_SYSTEM_H

#include <raylib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG_FMT_RESET "\x1b[0m"
#define LOG_FMT_WARNING "\x1b[33m"
#define LOG_FMT_ERROR "\x1b[31m"

// clang-format off

/**
  Pretty much an alias for printf, except it inserts a '\n' character at the
  end. Meant to be used in the Lua API as `system.log()`.
*/
#define SYSTEM_LOG(...) \
do { \
printf(__VA_ARGS__); \
puts(""); \
} while (0)


/**
  A macro that prints out the given message in the format of a warning.
*/
#define SYSTEM_WARN_LOG(...) \
do { \
  printf(LOG_FMT_WARNING "WARNING: "); \
  printf(__VA_ARGS__); \
  puts(LOG_FMT_RESET ""); \
} while (0)

/**
  A macro that prints out the given message in the format of an error message.
*/
#define SYSTEM_ERROR_LOG(...) \
do { \
  printf(LOG_FMT_ERROR "ERROR: "); \
  printf(__VA_ARGS__); \
  puts(LOG_FMT_RESET ""); \
} while (0)

/**
  A macro that prints out a message formatted as a fatal error.
*/
#define SYSTEM_PANIC_LOG(...) \
do { \
  printf(LOG_FMT_ERROR "FATAL ERROR: "); \
  printf(__VA_ARGS__); \
  puts(LOG_FMT_RESET ""); \
} while (0)

/**
  A macro that returns the current time in unix timestamp format.
*/
#define SYSTEM_GET_TIME() ((size_t)time(NULL))

// clang-format on

/**
  Payload used to initialize the runtime.
*/
typedef struct {
  bool fullscreen;
} sys_args_t;

/**
  Returns the system tick (how many interrupts have been executed).
*/
const size_t system_tick(void);

/**
  Returns the system framebuffer.
*/
RenderTexture2D* system_get_framebuffer(void);

/**
  Initializes the system window.
*/
int system_init(sys_args_t args);

/**
  Causes the system to interrupt. During an interrupt, the swap chain swaps
  buffers, the input refreshes, and the current tick is incremented.
*/
void system_interrupt(void);

/**
  Deletes the system window along with all resources related to it.
*/
void system_free(void);

#endif
