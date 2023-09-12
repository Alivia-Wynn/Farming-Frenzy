#ifndef CHARACTER_H
#define CHARACTER_H
#include "baseCharacter.h"


class Character : public BaseCharacter
{
public:
    Character(int winwidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisonRec(){return weaponCollisionRec;}
    float getHealth() const {return health;}
    void takeDamage (float damage);
    void gainPoints(float points);
    float getScore() const {return score;}
    virtual Rectangle GetCollisionRec() override;
    void setHealth(float add){ health += add;}

private:
   int windowWidth{};
   int windowHeight{};
   Texture2D weapon {LoadTexture("textures/characters/axe.png")};
   Rectangle weaponCollisionRec {};
   float health{100.f};
   float score {0};
};
#endif