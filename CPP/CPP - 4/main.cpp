#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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
        Vector2{800.f, 300.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f}, 
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies) {
        enemy->setTarget(&knight);
    }

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

        if (knight.getAlive()) {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        } else {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
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

        for (auto enemy : enemies) {
            enemy->tick(GetFrameTime());

            if (
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
                CheckCollisionRecs(enemy->getCollisonBox(), knight.getWeaponCollisonBox())
            ) {
                enemy->setAlive(false);
            }
        }

        EndDrawing();
    }
    UnloadTexture(background);
    knight.UnloadTextures();
    for (auto enemy : enemies) {
        enemy->UnloadTextures();
    }
    CloseWindow();
}