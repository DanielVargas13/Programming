#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex) :
    idle(idleTex),
    run(runTex),
    currentTex(idleTex),
    worldPos(pos)
{
    width = currentTex.width / maxFrame;
    height = currentTex.height;
}

void Enemy::tick(float deltaTime)
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

void Enemy::undoMovemnt()
{
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisonBox() {
    return Rectangle{
        x: screenPos.x,
        y: screenPos.y,
        width: width * scale,
        height: height * scale
    };
}