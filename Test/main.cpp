#include "raylib.h"
#include "raymath.h"

using namespace std;

int main()
{
    int WindowWidth = 600;
    int WindowHeight = 800;

    InitWindow(WindowWidth, WindowHeight, "Test");

    Texture2D map = LoadTexture("background/NewMap2.png");
    Vector2 mapPos = {};

    Texture2D Character = LoadTexture("characters/Basic_Charakter_Spritesheet.png");
    int Character_width = Character.width;
    int Character_height = Character.height;
    Rectangle source = {0.0f, 0.0f, (float)Character_width / 4, Character_height / 4};
    Rectangle dest = {0.0f, 0.0f, Character_width / 2, Character_height / 2};
    Vector2 origin = {};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 velocity = {};
        if (IsKeyDown(KEY_A))
            velocity.x -= 1;
        if (IsKeyDown(KEY_D))
            velocity.x += 1;
        if (IsKeyDown(KEY_W))
            velocity.y -= 1;
        if (IsKeyDown(KEY_S))
            velocity.y += 1;

        if (Vector2Length(velocity) != 0.0)
        {
            mapPos = Vector2Subtract(mapPos, Vector2Normalize(velocity));
        }

        DrawTextureEx(map, mapPos, 0.0f, 1, WHITE);

        DrawTexturePro(Character, source, dest, origin, 0.0f, WHITE);
        DrawRectangleLines(0, 0, Character_width / 2, Character_height / 2, WHITE);

        EndDrawing();
    }

    CloseWindow();
}
