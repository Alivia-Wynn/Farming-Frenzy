#include "raylib.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
    public:
        BaseCharacter();
        Vector2 getWorldPos()
        {
            return worldPos;
        }
        void undoMovement();
        virtual Rectangle GetCollisionRec();
        virtual void tick(float deltaTime);
        virtual Vector2 getScreenPos() = 0;
        bool getAlive(){ return alive; }
        void setAlive(bool isAlive){ alive = isAlive; }

    protected:
        Texture2D texture{LoadTexture("characters/rabbit_down.png")};
        Texture2D idle{LoadTexture("characters/rabbit_down.png")};
        Texture2D down{LoadTexture("characters/rabbit_down2.png")};
        Texture2D up{LoadTexture("characters/rabbit_up.png")};
        Texture2D left{LoadTexture("characters/rabbit_left.png")};
        Texture2D right{LoadTexture("characters/rabbit_right1.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
   //    Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        Vector2 velocity{};
        // animation variables
        float runningTime{};
        float rightleft{1.f};
        int frame{};
        int maxFrame{4};
        int maxFrameEnemy{6};
        float updateTime{1.0 / 12.0};
        float speed{4.f};
        float width;
        float height;
        float scale{4.0f};
    private:
        bool alive {true};

};

#endif