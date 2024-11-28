#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex)
{
    idle = idleTex;
    run = runTex;
    currentTex = idleTex;
    worldPos = pos;
    width = currentTex.width / maxFrame;
    height = currentTex.height;
    speed = 3.0f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive()) return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(target->getCollisonBox(), getCollisonBox())) {
        target->takeDamage(dps * deltaTime);
    }
}

Vector2 Enemy::getScreenPos() 
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}