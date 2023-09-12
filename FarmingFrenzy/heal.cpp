#include "heal.h"
#include "raymath.h"

Heal::Heal(Vector2 pos, Texture2D healTexture){
    worldPos = pos;
    texture = healTexture;
    width = texture.width;
    height = texture.height;
}

void Heal::tick(float deltaTime){
    Rectangle source = { width, 0.f, width, height};
    Rectangle dest = {getScreenPos().x, getScreenPos().y, scale *width , scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if (CheckCollisionRecs(target->getWeaponCollisonRec(), GetCollisionRec())){
         target -> setHealth(healthAdded);
        }
    }
}

Vector2 Heal::getScreenPos(){
    return Vector2Add(worldPos, target ->getWorldPos());
}

Rectangle Heal::GetCollisionRec(){
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        texture.width * scale,
        texture.height * scale
    };
}
