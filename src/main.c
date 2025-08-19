/**
  src/main.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "api/intro.h"
#include "api/init.h"
#include "lualib/init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char game_path[260];
  bool fullscreen;
  bool cut_intro;
}  runtime_args_t;

/**
  Returns the number of '-' characters at the start of the string. Can be used
  to discern between short and long arguments.
*/
int get_slashes(const char* str) {
  int result = 0;
  while (str[result] == '-')
    result++;
  return result;
}

/**
  Displays the help message and exits the application.
*/
void display_help(void) {
  // clang-format off
  printf(
"V-GAME\n"
"==============================================================================\n"
"*The most basic vector-based virtual game console.*\n"
"\n"
"## FLAGS:\n"
"-f, --fullscreen: Runs the runtime in fullscreen.\n"
"-c, --cut-intro: Skips the intro screen.\n"
"-h, --help: Displays this message.\n"
  );
  // clang-format on

  exit(0);
}

/**
  Parses all arguments passed through `argc` and `argv` within the entry point.
  Exits the application if the given command-line flags are invalid.
*/
runtime_args_t parse_args(int argc, char** argv) {
  if (argc < 2) {
    SYSTEM_PANIC_LOG("Nothing to run!");
    exit(-1);
  }

  runtime_args_t runtime_args = {0};
  for (int i = 1; i < argc; i++) {
    const char* current_arg = argv[i];
    int slashes = get_slashes(current_arg);

    switch (slashes) {
    case 1: {
      int arg_length = strlen(current_arg);
      if (arg_length > 2) {
        SYSTEM_PANIC_LOG("Invalid flag \"%s\"!", current_arg);
        exit(-1);
      }

      switch (current_arg[1]) {
      case 'f':
        runtime_args.fullscreen = true;
        break;

      case 'c':
        runtime_args.cut_intro = true;
        break;

      case 'h':
        display_help();

      default:
        SYSTEM_PANIC_LOG("Invalid flag \"%s\"!", current_arg);
        exit(-1);
      }
    } break;

    case 2: // Parse long argument:
    {
      if (strcmp(current_arg, "--fullscreen") == 0) {
        runtime_args.fullscreen = true;
      } else if (strcmp(current_arg, "--cut-intro") == 0) {
        runtime_args.cut_intro = true;
      } else if (strcmp(current_arg, "--help") == 0) {
        display_help();
      } else {
        SYSTEM_PANIC_LOG("Invalid flag \"%s\"!", current_arg);
        exit(-1);
      }
    } break;

    default: // Attempt to parse the file path.
    {
      int path_length = strlen(current_arg);
      strncpy(runtime_args.game_path, current_arg, path_length);

      if (current_arg[path_length - 1] == '\\' ||
          current_arg[path_length - 1] == '/') {
        strcat(runtime_args.game_path, "init.lua");
      } else if (strcmp(&current_arg[path_length - 4], ".lua") != 0) {
        strcat(runtime_args.game_path, ".lua");
      }

    } break;
    }
  }

  return runtime_args;
}

/**
  Frees all resources related to the runtime.
*/
void free_runtime(void) {
  vlua_free();
  api_free();
  SYSTEM_LOG("All resources released!");
}

/**
  Starts the runtime with the given command-line arguments.
*/
int start_runtime(runtime_args_t args) {
  if (atexit(free_runtime)) {
    SYSTEM_PANIC_LOG("%s", "Failed to register cleanup functions!");
    return 1;
  }

  // Initialize game window. //
  sys_args_t sys_args = {.fullscreen = args.fullscreen};
  api_init(sys_args);

  if (!args.cut_intro)
    intro_play();

  // Initialize the Lua runtime.
  SYSTEM_LOG("Executing game at %s", args.game_path);

  int exit_status = vlua_init(args.game_path);
  if (exit_status)
    return exit_status;

  api_free();
  return 0;
}


#if defined(_WIN32) && defined(BUILD_RELEASE)

/**
  The entry point of the applictation for windows systems built in release
  mode.
*/
int WinMain(void) {
  return start_runtime(parse_args(argc, argv));
}

#else

/**
  The entry point of the application for all unix systems and for windows
  systems built in debug mode.
*/
int main(int argc, char** argv) {
  return start_runtime(parse_args(argc, argv));
}

#endif

