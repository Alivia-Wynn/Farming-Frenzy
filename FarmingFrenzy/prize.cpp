#include "prize.h"
#include "raymath.h"

Prize::Prize(Vector2 pos, Texture2D prizeTexture){
    worldPos = pos;
    texture = prizeTexture;
    width = texture.width;
    height = texture.height;
}

void Prize::tick(float deltaTime){
    if (!getAlive()) return;
    Rectangle source = { width, 0.f, width, height};
    Rectangle dest = {getScreenPos().x, getScreenPos().y, scale *width , scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if (CheckCollisionRecs(target->getWeaponCollisonRec(), GetCollisionRec())){
         target -> gainPoints(points);
        }
    }
}

Vector2 Prize::getScreenPos(){
    return Vector2Add(worldPos, target ->getWorldPos());
}

Rectangle Prize::GetCollisionRec(){
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        texture.width * scale,
        texture.height * scale
    };
}
