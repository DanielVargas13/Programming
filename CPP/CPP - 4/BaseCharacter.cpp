#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {}

void BaseCharacter::undoMovemnt()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisonBox() {
    return Rectangle{
        x: getScreenPos().x,
        y: getScreenPos().y,
        width: width * scale,
        height: height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }

        if (Vector2Length(velocity) != 0.0)
    {
        Vector2 normalizedDirection = Vector2Normalize(velocity);
        worldPos = Vector2Add(worldPos, Vector2Scale(normalizedDirection, speed));
        rightLeft = velocity.x < 0.f ? -1.f : 1.f;
        currentTex = run;
    }
    else
    {
        currentTex = idle;
    }

    velocity = {};

    Rectangle source{
        x : frame * width,
        y : 0.f,
        width : rightLeft * width,
        height : height,
    };
    Rectangle dest{
        x : getScreenPos().x,
        y : getScreenPos().y,
        width : float(scale * width),
        height : float(scale * height),
    };

    DrawTexturePro(currentTex, source, dest, Vector2{}, 0.0, WHITE);
}