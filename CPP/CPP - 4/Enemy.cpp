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
}

void Enemy::tick(float deltaTime)
{
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);
}