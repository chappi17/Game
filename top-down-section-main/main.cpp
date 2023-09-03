#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"

int main()
{
    // Setting Window
    int WindowSize[2];
    WindowSize[0] = 384;
    WindowSize[1] = 384;

    InitWindow(WindowSize[0], WindowSize[1], "Classy Clan");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = {0.0, 0.0};
    const float mapScale = 4.0f;

    Character knight(WindowSize[0],WindowSize[1]);
    Prop rock= {Vector2{0.0f,0.0f},LoadTexture("nature_tileset/Rock.png")};
  
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.GetwolrdPos(), -1.0f);

        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

        rock.Render(knight.GetwolrdPos());


        knight.Tick(GetFrameTime());

        // Check Map Bounds
        if (knight.GetwolrdPos().x < 0.0f ||
            knight.GetwolrdPos().y < 0.0f ||
            knight.GetwolrdPos().x + WindowSize[0] > map.width * mapScale ||
            knight.GetwolrdPos().y + WindowSize[1] > map.height * mapScale)
                {
                    knight.undoMovement();
                }

            EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}
