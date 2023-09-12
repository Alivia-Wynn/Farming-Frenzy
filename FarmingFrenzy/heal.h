#ifndef HEAL_H
#define HEAL_H
#include "baseCharacter.h"
#include "character.h"


class Heal : public BaseCharacter
{
public:
    Heal(Vector2 pos, Texture2D healTexture);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    virtual Rectangle GetCollisionRec() override;
    void setWorldPos(Vector2 pos){worldPos = pos;}
    void setTarget(Character* character){
            target = character;
        };

private:
Character* target;
   float healthAdded{20.f};
};
#endif