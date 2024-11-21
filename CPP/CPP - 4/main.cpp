#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    // Window
    int windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Clash of Knights");

    // Map
    Texture2D background = LoadTexture("nature_tileset/cpp_map.png");
    Vector2 bgPos{0.0, 0.0};
    const float scale = 4.f;

    Character knight{windowDimensions[0], windowDimensions[1]};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        bgPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(background, bgPos, 0.0, scale, WHITE);

        knight.tick(GetFrameTime());

        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > 
                background.width * scale ||
            knight.getWorldPos().y + windowDimensions[1] > 
                background.height * scale) 
        {
            knight.undoMovemnt();
        }

        EndDrawing();
    }
    UnloadTexture(background);
    //UnloadTexture(knightIdle);
    //UnloadTexture(knightRun);
    CloseWindow();
}