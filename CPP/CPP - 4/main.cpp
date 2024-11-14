#include "raylib.h"
#include "raymath.h"

int main()
{
    // Window
    int windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Clash of Knights");

    // Map
    Texture2D background = LoadTexture("nature_tileset/cpp_map.png");
    Vector2 bgPos{0.0, 0.0};
    float speed = 4.0;

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        x: float(windowDimensions[0]/2.0 - 4.0 * ((knight.width/2)/6)),
        y: float(windowDimensions[1]/2.0 - 4.0 * (knight.height/2))
    };

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if (Vector2Length(direction) != 0.0) 
        {
            Vector2 normalizedDirection = Vector2Normalize(direction);
            bgPos = Vector2Subtract(bgPos, Vector2Scale(normalizedDirection, speed));
        }

        DrawTextureEx(background, bgPos, 0.0, 4.0, WHITE);

        Rectangle source{
            x: 0.f,
            y: 0.f,
            width: float(knight.width/6.f),
            height: float(knight.height),
        };
        Rectangle dest{
            x: knightPos.x,
            y: knightPos.y,
            width: float(4.f * knight.width/6),
            height: float(4.f * knight.height),
        };

        DrawTexturePro(knight, source, dest, Vector2{}, 0.0, WHITE);

        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(knight);
    CloseWindow();
}