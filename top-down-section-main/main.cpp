#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
#include "Enemy.h"
#include <string>

using namespace std;

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

    Character knight(WindowSize[0], WindowSize[1]);
    Enemy goblin{
        Vector2{500.0f, 400.0f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Prop backgrounds[2]{
        {Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        {Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy slime{
        Vector2{500.0f, 200.0f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};
    for (auto enemy : enemies)
    {
        enemy->SetTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.GetwolrdPos(), -1.0f);

        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

        // draw the props
        for (auto background : backgrounds)
        {
            background.Render(knight.GetwolrdPos());
        }
        bool gameiscomplete = false;
        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            string knightHealth = "Health: ";
            knightHealth.append(to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.0f, 45.0f, 40, RED);
        }

        knight.Tick(GetFrameTime());

        // Check Map Bounds
        if (knight.GetwolrdPos().x < 0.0f ||
            knight.GetwolrdPos().y < 0.0f ||
            knight.GetwolrdPos().x + WindowSize[0] > map.width * mapScale ||
            knight.GetwolrdPos().y + WindowSize[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }
        // Check prop Collision
        for (auto background : backgrounds)
        {
            if (CheckCollisionRecs(background.GetCollisionRec(knight.GetwolrdPos()), knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        // Check weapon Collision
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.GetCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}
