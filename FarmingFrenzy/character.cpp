# include "character.h"
# include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
   // screenPos = {
   //     (static_cast<float>(winWidth) / 2.0f - (scale * (.5f * (float)texture.width / 4.0f))) + 35,
   //     static_cast<float>(winHeight) / 2.0f - (scale * (.5f * (float)texture.height))};
  //  width =  texture.width/maxFrame;
   // height = texture.height;
}

Vector2 Character::getScreenPos(){
    return Vector2{
         (static_cast<float>(windowWidth) / 2.0f - (scale * (.5f * (float)texture.width / 4.0f))) + 35,
        static_cast<float>(windowHeight) / 2.0f - (scale * (.5f * (float)texture.height))
    };
}

void Character::tick(float deltaTime)
{
   // Vector2 direction{};
    float rightleft{1.f};
    worldPosLastFrame = worldPos;
    if (!getAlive()) return;


    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;

    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;

    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;

    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    if (Vector2Length(velocity) != 0.0)
    {
        // set  worldpos = worldPos + direction
        worldPos = Vector2Subtract(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
        runningTime += deltaTime;
        // update animation frame
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrame)
            {
                frame = 0;
            }
        }

        if (IsKeyDown(KEY_A))
            texture = left;
        if (IsKeyDown(KEY_D))
            texture = right;
        if (IsKeyDown(KEY_W))
            texture = up;
        if (IsKeyDown(KEY_S))
            texture = down;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    Rectangle source = { 2 * frame * (float)texture.width/4.f, 0.f,  (float)texture.width / 4.f, (float)texture.height};
    Rectangle dest = {getScreenPos().x, getScreenPos().y, (float)texture.width , scale * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);

    //draw sword
    Vector2 origin {};
    Vector2 offset {};
    float rotation {};
    if (rightleft > 0.f){
        origin = {0.f, weapon.height * scale};
        offset = {60.f,60.f};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ?  35.f : 0.f;
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
    }else{
        origin = {weapon.width * scale, weapon.height*scale};
        offset = {29.f,60.f};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ?  -35.f : 0.f;
        
        weaponCollisionRec = { 
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
    }
    Rectangle weapon_source{0.f, 0.f, static_cast<float>(weapon.width) * rightleft, static_cast<float>(weapon.height)};
    Rectangle weapon_dest { getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, weapon_source, weapon_dest, origin, rotation, WHITE);
  //  DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height , RED);
}   

void Character::takeDamage(float damage){
    health -= damage;
    if(health <= 0.f){
        setAlive(false);
    }
}
void Character::gainPoints(float points){
    score += points;
}
Rectangle Character::GetCollisionRec(){
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        texture.width/4.f * scale,
        texture.height * scale
    };
}
