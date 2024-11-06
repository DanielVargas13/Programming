#include "raylib.h"

int main() 
{
    int width = 350;
    InitWindow(width, 200, "Daniel's Window");

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
}