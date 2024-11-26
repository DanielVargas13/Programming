#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() {}

void BaseCharacter::undoMovemnt()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisonBox() {
    return Rectangle{
        x: screenPos.x,
        y: screenPos.y,
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