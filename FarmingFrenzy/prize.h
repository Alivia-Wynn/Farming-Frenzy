#ifndef PRIZE_H
#define PRIZE_H
#include "baseCharacter.h"
#include "character.h"


class Prize : public BaseCharacter
{
public:
    Prize(Vector2 pos, Texture2D prizeTexture);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    virtual Rectangle GetCollisionRec() override;
    void setWorldPos(Vector2 pos){worldPos = pos;}
    float getPoints() const {return points;}
    void setTarget(Character* character){
            target = character;
        };
    void setPoints(float new_points){points = new_points;}

private:
Character* target;
   float points{10.f};
};
#endif