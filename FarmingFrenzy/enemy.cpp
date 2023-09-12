#include "enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width;
    height = texture.height;
    speed = 3.5f;

}

void Enemy::tick(float deltaTime){
    if (!getAlive()) return;
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
   if (Vector2Length(velocity)< radius) velocity = {} ;
   BaseCharacter::tick(deltaTime);

   if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec())){
    target -> takeDamage(damagePerSec * deltaTime);
   }
   if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec())){
         target -> gainPoints(points);
        }
    }
}

Vector2 Enemy::getScreenPos(){
    return Vector2Add(worldPos, target ->getWorldPos());
}


Rectangle Enemy::GetCollisionRec(){
    return Rectangle{
        getScreenPos().x - 1,
        getScreenPos().y + 4,
        (texture.width/4.f) * 2,
        (float) texture.height * 2
    };
}