#ifndef RUNTIME_H
#define RUNTIME_H

#include <lua.h>
#include <lauxlib.h>
#include <raylib.h>
#include <stdio.h>
#include "lualib/vbase.h"
#include "lualib/graphics.h"

/**
  Payload used to initialize the runtime.
*/
typedef struct {
  const char* starting_game;
} runtime_args_t;

/**
  Initializes the console runtime.
*/
int runtime_init(runtime_args_t args);

/**
  Detects whether or not the application should close and closes the
  application if necessary. This function runs automatically during an
  interrupt.
*/
void runtime_check_close();

/**
  Interrupts the execution of the current program and causes a frame to skip.
*/
void runtime_interrupt();

/**
  Skips the given amount of frames.
*/
void runtime_sleep(int frames);

/**
  Causes the program to panic, printing the given message to the console and
  freeing any resources related to the runtime.
*/
void runtime_panic(const char* msg);



#endif

