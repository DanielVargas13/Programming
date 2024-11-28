#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* current) { target = current; }
    virtual Vector2 getScreenPos() override;
private:
    Character* target{};
    float dps = 10.f;
    float radius = 25.f;
};