#include "raylib.h"
#include "raymath.h"

int main()
{
    // Setting Window
    int WindowSize[2];
    WindowSize[0] = 384;
    WindowSize[1] = 384;

    InitWindow(WindowSize[0],WindowSize[1],"Classy Clan");

    Texture2D map = LoadTexture("nature_tileset/NewMap.png");
    Vector2 mapPos = {0.0,0.0};
   float speed = 4;

   Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
   Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
   Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
   Vector2 knightPos = 
   {
    WindowSize[0]/2.0f - 4.0f* (0.5f * (float)knight.width/6.0f),
    WindowSize[1]/2.0f - 4.0f* (0.5f * (float)knight.height)
   };

// 1 : facing right  -1: facing left
   float rightLeft = 1.0f;
 

   // animation variables
float runningTime= 0;
int frame =0;
const int maxframes = 6;
// if updateTime is smaller -> fast
const float updateTime = 1.0f/24.0f;

SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction={};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if(Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            // set Scale = normalize(direction), speed
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction),speed));

            direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
            knight = knight_run;
        }
        else 
        {
            knight = knight_idle;
        }


        DrawTextureEx(map,mapPos,0.0f,4.0,WHITE);
        // update animation frame
        runningTime += GetFrameTime();
        if(runningTime >= updateTime)
        {
            frame++;
            runningTime =0.0f;

            if (frame > maxframes) frame =0;
        }


        // draw the character
        // character's one frame rectangle
        Rectangle source = {frame * (float)knight.width/6.0f,0.0f,rightLeft * (float)knight.width/6.0f,(float)knight.height};
        // character's draw destination + size is * 4 because of window size
        Rectangle dest = {knightPos.x,knightPos.y, 4.0f *knight.width/6.0f,4.0f* knight.height};
        // the point of rotation.
        Vector2 origin = {};
        DrawTexturePro(knight,source,dest,origin,0.0f,WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knight_run);
    UnloadTexture(knight_idle);
    UnloadTexture(knight);

    CloseWindow();
    
}