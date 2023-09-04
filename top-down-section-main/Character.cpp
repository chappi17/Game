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
    BaseCharacter::Tick(deltaTime);

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


}


