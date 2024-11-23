#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

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

    Prop props[2] {
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
    };

    Enemy goblin{
        Vector2{}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        bgPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(background, bgPos, 0.0, scale, WHITE);

        for (auto prop : props) 
        {
            prop.Render(knight.getWorldPos());
        }

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

        for (auto prop : props) 
        {
            if (CheckCollisionRecs(
                knight.getCollisonBox(), 
                prop.getCollisonBox(knight.getWorldPos())
                )) 
            {
                knight.undoMovemnt();
            }
        }

        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(background);
    //UnloadTexture(knightIdle);
    //UnloadTexture(knightRun);
    CloseWindow();
}