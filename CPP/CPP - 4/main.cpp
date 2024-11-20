#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int windowWidth, int windowHeight);
    void tick(float deltaTime);

private:
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D currentTex = idle;
    Vector2 screenPos{};
    Vector2 worldPos{};
    float rightLeft = 1.f;
    float runningTime{};
    int frame{};
    const int maxFrame = 6;
    const float updateTime = 1.f / 12.f;
    const float speed = 4.f;
};

void Character::setScreenPos(int windowWidth, int windowHeight)
{
    screenPos = {
        x : float(windowWidth / 2.0 - 4.0 * ((currentTex.width / 2) / 6)),
        y : float(windowHeight / 2.0 - 4.0 * (currentTex.height / 2))
    };
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        Vector2 normalizedDirection = Vector2Normalize(direction);
        worldPos = Vector2Add(worldPos, Vector2Scale(normalizedDirection, speed));
        rightLeft = direction.x < 0.f ? -1.f : 1.f;
        currentTex = run;
    }
    else
    {
        currentTex = idle;
    }

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }

    Rectangle source{
        x : frame * float(currentTex.width / 6.f),
        y : 0.f,
        width : rightLeft * float(currentTex.width / 6.f),
        height : float(currentTex.height),
    };
    Rectangle dest{
        x : screenPos.x,
        y : screenPos.y,
        width : float(4.f * currentTex.width / 6),
        height : float(4.f * currentTex.height),
    };

    DrawTexturePro(currentTex, source, dest, Vector2{}, 0.0, WHITE);
}

int main()
{
    // Window
    int windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Clash of Knights");

    // Map
    Texture2D background = LoadTexture("nature_tileset/cpp_map.png");
    Vector2 bgPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowDimensions[0], windowDimensions[1]);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        bgPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(background, bgPos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(background);
    //UnloadTexture(knightIdle);
    //UnloadTexture(knightRun);
    CloseWindow();
}