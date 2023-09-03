#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width/maxframes;
    height = texture.height;
        screenPos =
        {
            static_cast<float>(winWidth) / 2.0f - scale * (0.5f * (float)width),
            static_cast<float>(winHeight) / 2.0f - scale * (0.5f * (float)height)
        };
}

Character::~Character()
{
}


void Character::Tick(float deltaTime)
{
    WorldPostLastFrame = worldPos;
    Vector2 direction = {};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos - direction
        // set Scale = normalize(direction), speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;

        if (frame > maxframes)
            frame = 0;
    }

    // draw the character
    // character's one frame rectangle
    Rectangle source = {frame * (float)width, 0.0f, rightLeft * (float)width, (float)height};
    // character's draw destination + size is * 4 because of window size
    Rectangle dest = {screenPos.x, screenPos.y, scale * (float)width, scale * (float)height};
    // the point of rotation.
    Vector2 origin = {};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

void Character::undoMovement()
{
    worldPos = WorldPostLastFrame;
}
