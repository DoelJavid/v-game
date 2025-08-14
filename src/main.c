
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "runtime.h"

#ifdef _WIN32
// int WinMain(void) {
int main(int argc, char** argv) {
#else
int main(int argc, char** argv) {
#endif
  if (argc < 2) {
    printf("Nothing to run!");
    return -1;
  }

  runtime_args_t runtime_args = {
    .starting_game = argv[1]
  };

  return runtime_init(runtime_args);
}

