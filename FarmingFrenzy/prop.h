#include "raylib.h"

class Prop{
    public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 rabbitPos);
    Rectangle GetCollisionRec(Vector2 rabbitPos);
    void setWorldPos(Vector2 new_pos){worldPos = new_pos;}


    private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
};