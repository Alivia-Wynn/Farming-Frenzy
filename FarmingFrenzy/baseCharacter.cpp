#include "baseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){
    
}

void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec(){
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        texture.width * scale,
        texture.height * scale
    };
}

void BaseCharacter::tick(float deltaTime){
     worldPosLastFrame = worldPos;


    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
        {
            frame = 0;
        }
    }
    if (Vector2Length(velocity) != 0.0)
    {
        // set  worldpos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    //draw the character
    Rectangle source = { frame * width/4.f, 0.f, (rightleft * width/scale), height};
    Rectangle dest = {getScreenPos().x, getScreenPos().y, width , scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}