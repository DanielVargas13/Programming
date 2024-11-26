#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovemnt();
    Rectangle getCollisonBox();
    virtual void tick(float deltaTime);
protected:
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D currentTex = idle;
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    float rightLeft = 1.f;
    float runningTime{};
    int frame{};
    int maxFrame = 6;
    float updateTime = 1.f / 12.f;
    float speed = 4.f;
    float width{};
    float height{};
    float scale = 4.f;
};

#endif