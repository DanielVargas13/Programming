#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int windowWidth, int windowHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisonBox() { return weaponCollisonBox; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
    virtual void UnloadTextures() override;
private:
    int winWidth{};
    int winHeight{};
    Texture2D weapon{ LoadTexture("characters/weapon_sword.png") };
    Rectangle weaponCollisonBox{};
    float health = 100.f;
};

#endif