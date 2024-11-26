#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight) 
{
    width = currentTex.width / maxFrame;
    height = currentTex.height;

    screenPos = {
        x : static_cast<float>(windowWidth) / 2.f - scale * (width / 2),
        y : static_cast<float>(windowHeight) / 2.f - scale * (height / 2)
    };
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

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
}