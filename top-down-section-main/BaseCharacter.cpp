#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::Tick(float deltaTime)
{
    WorldPostLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;

        if (frame > maxframes)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos - direction
        // set Scale = normalize(direction), speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // draw the character
    Rectangle source = {frame * (float)width, 0.0f, rightLeft * (float)width, (float)height};
    Rectangle dest = {getScreenPos().x, getScreenPos().y, scale * (float)width, scale * (float)height};
    Vector2 origin = {};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = WorldPostLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle
    {
        getScreenPos().x,
        getScreenPos().y,
        width*scale,
        height*scale
    };
}