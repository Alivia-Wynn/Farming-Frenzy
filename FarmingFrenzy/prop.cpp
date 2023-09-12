#include "prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) :
texture(tex),
worldPos(pos)

{

}

void Prop::Render(Vector2 rabbitPos)
{
Vector2 screenPos = Vector2Add(worldPos, rabbitPos);
DrawTextureEx(texture,screenPos,0.f, scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 rabbitPos){
    Vector2 screenPos = Vector2Add(worldPos, rabbitPos);
    return Rectangle{
            //location
                screenPos.x,
                screenPos.y,
            // dimensions
                texture.width * scale,
                texture.height * scale
    };
}