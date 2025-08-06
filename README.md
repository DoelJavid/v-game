V-GAME
===============================================================================
*The most basic vector-based virtual game console.*

V-GAME is a console runtime that's made using C, Lua, and Raylib.

## How to Build

To build the project, you need to have scons installed on your computer. you
also need to have the static-link libraries for Lua and raylib.

Once you've obtained static link libraries for Lua and Raylib, place the
static-link libraries into the lib directory, then run `scons -j6`. Replace 6
with how many threads are in your computer.

You can build the project for release using `scons -j6 --release`. This uses
similar syntax for debug mode.

