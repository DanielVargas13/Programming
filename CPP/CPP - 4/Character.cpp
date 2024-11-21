#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight) {
    width = currentTex.width / maxFrame;
    height = currentTex.height;

    screenPos = {
        x : static_cast<float>(windowWidth) / 2.f - scale * (width / 2),
        y : static_cast<float>(windowHeight) / 2.f - scale * (height / 2)
    };
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

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
        x : frame * width,
        y : 0.f,
        width : rightLeft * width,
        height : height,
    };
    Rectangle dest{
        x : screenPos.x,
        y : screenPos.y,
        width : float(scale * width),
        height : float(scale * height),
    };

    DrawTexturePro(currentTex, source, dest, Vector2{}, 0.0, WHITE);
}

void Character::undoMovemnt()
{
    worldPos = worldPosLastFrame;
}