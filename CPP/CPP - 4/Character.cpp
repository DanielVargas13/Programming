#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight) :
    winWidth(windowHeight),
    winHeight(windowHeight)
{
    width = currentTex.width / maxFrame;
    height = currentTex.height;
}

Vector2 Character::getScreenPos() 
{
    return Vector2{
        static_cast<float>(winWidth) / 2.f - scale * (width / 2),
        static_cast<float>(winHeight) / 2.f - scale * (height / 2)
    };
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;
    
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f) {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisonBox = {
            x: getScreenPos().x + offset.x,
            y: getScreenPos().y + offset.y - (weapon.height * scale),
            width: scale * weapon.width,
            height: scale * weapon.height
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    } else {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisonBox = {
            x: getScreenPos().x + offset.x - (scale * weapon.width),
            y: getScreenPos().y + offset.y - (weapon.height * scale),
            width: scale * weapon.width,
            height: scale * weapon.height
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }

    Rectangle source{
        x : 0.f,
        y : 0.f,
        width : static_cast<float>(weapon.width) * rightLeft,
        height : static_cast<float>(weapon.height),
    };
    Rectangle dest{
        x : getScreenPos().x + offset.x,
        y : getScreenPos().y + offset.y,
        width : scale * weapon.width,
        height : scale * weapon.height,
    };

    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::takeDamage(float damage) 
{
    health -= damage;
    if (health <= 0.f) {
        setAlive(false);
    }
}

void Character::UnloadTextures() {
    UnloadTexture(weapon);
    BaseCharacter::UnloadTextures();
}