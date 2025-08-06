
#include <raylib.h>

#ifdef _WIN32
int WinMain(void) {
#else
int main(void) {
#endif
  InitWindow(800, 600, "V-Game");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

