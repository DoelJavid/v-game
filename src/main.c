
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runtime.h"

/**
  Returns the number of '-' characters at the start of the string.
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
void display_help() {
  printf(
"V-GAME\n"
"==============================================================================\n"
"*The most basic vector-based virtual game console.*\n"
"\n"
"## FLAGS:\n"
"-f, --fullscreen: Runs the runtime in fullscreen.\n"
"-h, --help: Displays this message.\n"
  );
  exit(0);
}

/**
  The main function of the applictation.
*/
#ifdef _WIN32
// int WinMain(void) {
int main(int argc, char** argv) {
#else
int main(int argc, char** argv) {
#endif

  if (argc < 2) {
    printf("Nothing to run!\n");
    return -1;
  }

  runtime_args_t runtime_args = {0};
  char game_path[260] = "";

  for (int i = 1; i < argc; i++) {
    const char* current_arg = argv[i];
    int slashes = get_slashes(current_arg);

    switch (slashes) {
    case 1:
      {
        int arg_length = strlen(current_arg);
        if (arg_length > 2) {
          printf("Invalid flag \"%s\"!\n", current_arg);
          return 1;
        }

        switch (current_arg[1]) {
        case 'f':
          runtime_args.fullscreen = true;
          break;

        case 'h':
          display_help();

        default:
          printf("Invalid flag \"%s\"!\n", current_arg);
          return 1;
        }
      } break;

    case 2: // Parse long argument:
      {
        if (strcmp(current_arg, "--fullscreen") == 0) {
          runtime_args.fullscreen = true;
        } else if (strcmp(current_arg, "--help") == 0) {
          display_help();
        } else {
          printf("Invalid flag \"%s\"!\n", current_arg);
          return 1;
        }
      } break;

    default: // Attempt to parse the file path.
      {
        int path_length = strlen(current_arg);
        strncpy(game_path, current_arg, path_length);

        if (
          current_arg[path_length - 1] == '\\' ||
          current_arg[path_length - 1] == '/'
        ) {
          strcat(game_path, "init.lua");
        } else if (strcmp(&current_arg[path_length - 4], ".lua") != 0) {
          strcat(game_path, ".lua");
        }

        runtime_args.starting_game = game_path;
      } break;
    }
  }

  if (!runtime_args.starting_game) {
    printf("Nothing to run!\n");
    return -1;
  }

  return runtime_init(runtime_args);
}

