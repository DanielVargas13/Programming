#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovemnt();
    Rectangle getCollisonBox();
private:
    Texture2D idle{};
    Texture2D run{};
    Texture2D currentTex{};
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