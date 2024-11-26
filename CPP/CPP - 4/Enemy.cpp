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
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos() 
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}