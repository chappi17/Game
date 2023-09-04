#include "BaseCharacter.h"

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

    // draw the character
    Rectangle source = {frame * (float)width, 0.0f, rightLeft * (float)width, (float)height};
    Rectangle dest = {screenPos.x, screenPos.y, scale * (float)width, scale * (float)height};
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
        screenPos.x,
        screenPos.y,
        width*scale,
        height*scale
    };
}