#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include "prize.h"
#include "heal.h"
#include <string>
#include <random>
#include <iostream>

// all references to a rabbit in the code refer to the user character
//  I thought the sprite was a rabbit

int main()
{
     const int windowWidth = 384;
     const int windowHeight = 384;
    

    InitWindow(windowWidth, windowHeight, "Farm Frenzy");
    SetTargetFPS(60);
    InitAudioDevice();
    Music bg_music = LoadMusicStream("music.mp3");  
    PlayMusicStream(bg_music);

    Texture2D map = LoadTexture("textures/nature_tileset/map.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    //initialize random number generator 
    std:: random_device rd;
    std::uniform_int_distribution<int> dist(100, 4000);

    //create character
    Character rabbit{windowWidth, windowHeight};

    //create enemies
    Enemy cow{
        Vector2{800.f, 300.f},
        LoadTexture("characters/Free Cow Sprites idle.png"),
        LoadTexture("characters/Free Cow Sprites.png")};
    Enemy chicken{
        Vector2{500.f, 700.f},
        LoadTexture("characters/Free Chicken Sprites idle.png"),
        LoadTexture("characters/Free Chicken Sprites.png")};
    Enemy cow2{
        Vector2{1000.f, 300.f},
        LoadTexture("characters/Free Cow Sprites idle.png"),
        LoadTexture("characters/Free Cow Sprites.png")};
    Enemy chicken2{
        Vector2{500.f, 2000.f},
        LoadTexture("characters/Free Chicken Sprites idle.png"),
        LoadTexture("characters/Free Chicken Sprites.png")};
    Enemy *enemies[]{
        &cow,
        &chicken,
        &cow2,
        &chicken2};

    //set the target to user so that the enemies will follow the user
    for (auto enemy : enemies)
    {
        enemy->setTarget(&rabbit);
    }


    //create prizes at random locations
    Prize prize{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/egg.png")
    };

    Prize egg2{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/egg.png")
    };

    Prize egg3{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/egg.png")
    };

    Prize egg4{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/egg.png")
    };

    Prize milk{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/milka.png")
    };

    Prize milk2{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/milk.png")
    };
    Prize milk3{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/milka.png")
    };

    Prize milk4{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/milk.png")
    };
    Prize milk5{
        Vector2{(float)dist(rd),(float)dist(rd)},
         LoadTexture("textures/nature_tileset/milka.png")
    };

    
    Prize *prizes[]{
        &prize,
        &egg2,
        &egg3,
        &egg4,
        &milk,
        &milk2,
        &milk3,
        &milk4,
        &milk5

       };
    for (auto prize : prizes){
        prize-> setTarget(&rabbit);
    }

    Heal apple{
         Vector2{1800.f, 700.f},
         LoadTexture("textures/nature_tileset/apple.png")
    };
    Heal apple2{
         Vector2{300.f, 1800.f},
         LoadTexture("textures/nature_tileset/apple.png")
    };
    Heal *heals[]{
        &apple,
        &apple2
    };
    for (auto heal : heals){
        heal-> setTarget(&rabbit);
    }

    //create obstacles throughout the map
    Prop props[12]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("textures/nature_tileset/Rock.png")},
        Prop{Vector2{1000.f, 900.f}, LoadTexture("textures/nature_tileset/Tree.png")},
        Prop{Vector2{2000.f, 1000.f}, LoadTexture("textures/nature_tileset/Tree.png")},
        Prop{Vector2{500.f, 2000.f}, LoadTexture("textures/nature_tileset/Tree.png")},
        Prop{Vector2{3000.f, 900.f}, LoadTexture("textures/nature_tileset/Free_Chicken_House.png")},
        Prop{Vector2{1000.f, 90.f}, LoadTexture("textures/nature_tileset/home.png")},
        Prop{Vector2{1500.f, 800.f}, LoadTexture("textures/nature_tileset/mushroom.png")},
        Prop{Vector2{300.f, 900.f}, LoadTexture("textures/nature_tileset/mushroom.png")},
        Prop{Vector2{900.f, 900.f}, LoadTexture("textures/nature_tileset/mushroom2.png")},
        Prop{Vector2{2000.f, 900.f}, LoadTexture("textures/nature_tileset/mushroom2.png")},
        Prop{Vector2{4000.f, 2000.f}, LoadTexture("textures/nature_tileset/mushroom2.png")},

        Prop{Vector2{400.f, 500.f}, LoadTexture("textures/nature_tileset/log.png")}};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        UpdateMusicStream(bg_music);
        mapPos = Vector2Scale(rabbit.getWorldPos(), 1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        for (auto prop : props)
        {
            prop.Render(rabbit.getWorldPos());
        }


        // print scores, health, game over to the screen
        if (!rabbit.getAlive())
        {
            DrawText("Game Over", 100, 100.f, 40, PINK);
            std::string score = "Final Score: ";
            score.append(std::to_string(rabbit.getScore()), 0, 5);
            DrawText(score.c_str(), 95, 200.f, 30, YELLOW);
            EndDrawing();
            continue;
        }
        else
        {
            std::string rabbitHealth = "Energy: ";
            rabbitHealth.append(std::to_string(rabbit.getHealth()), 0, 5);
            DrawText(rabbitHealth.c_str(), 10, 45.f, 20, PINK);
            
            
            std::string score = "Score: ";
            score.append(std::to_string(rabbit.getScore()), 0, 5);
            DrawText(score.c_str(), 245, 45.f, 20, YELLOW);
            
        }
        rabbit.tick(GetFrameTime());
        if (rabbit.getWorldPos().x < (-map.width * mapScale) + 400 ||
            rabbit.getWorldPos().y < (-map.height * mapScale) + 420 ||
            rabbit.getWorldPos().x > 0 ||
            rabbit.getWorldPos().y > 0)
        {
            rabbit.undoMovement();
        }

        // check for collisions with props
        for (auto prop : props)
        {
            // DrawRectangleLines(prop.GetCollisionRec(rabbit.getWorldPos()).x,prop.GetCollisionRec(rabbit.getWorldPos()).y,prop.GetCollisionRec(rabbit.getWorldPos()).width, prop.GetCollisionRec(rabbit.getWorldPos()).height, RED);
            if (CheckCollisionRecs(prop.GetCollisionRec(rabbit.getWorldPos()), rabbit.GetCollisionRec()))
            {
                rabbit.undoMovement();
            }
        }
      
      //animate the enemies
        for (auto enemy : enemies)
        {
         enemy->tick(GetFrameTime());
        }
        //check if user has clicked the enemy
        for (auto enemy : enemies)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), rabbit.getWeaponCollisonRec()))
                {
                    enemy->setWorldPos({(float)dist(rd),(float)dist(rd)});
                    
                }
            }
        }
        for (auto prize : prizes)
        {
            //prizes and heals aren't animated. the tick function just draws them to the screen
            prize->tick(GetFrameTime());
        }

        //check if prizes have been clicked on, if so move them to a new location
        for (auto prize : prizes)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionRecs(prize->GetCollisionRec(), rabbit.getWeaponCollisonRec()))
                {
                    prize->setWorldPos({(float)dist(rd),(float)dist(rd)});

                }
            }
            
        }
        for (auto heal : heals)
        {
            heal->tick(GetFrameTime());
        }
        for (auto heal : heals)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionRecs(heal->GetCollisionRec(), rabbit.getWeaponCollisonRec()))
                {
                    heal->setWorldPos({(float)dist(rd),(float)dist(rd)});
                    

                }
            }
            
        }
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}