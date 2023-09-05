#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : 
windowWidth(winWidth),
windowHeight(winHeight)
{
    width = texture.width / maxframes;
    height = texture.height;
}

Character::~Character()
{
}

void Character::Tick(float deltaTime)
{
    if(!getAlive()) return; 

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::Tick(deltaTime);

    Vector2 origin {};
    Vector2 offset {};
    float rotation = {};
    if(rightLeft > 0.0f) // right
    {
        origin = {0.0f,weapon.height * scale};
        offset = {40.0f,55.0f};
        weaponCollisionRec = 
        {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.0f : 0.0f;
    }
    else //left
    {
        origin = {weapon.width*scale, weapon.height * scale};
        offset = {25.0f,55.0f};
               weaponCollisionRec = 
        {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.0f : 0.0f;
    }

    // draw the sword
    Rectangle source {0.0f,0.0f, static_cast<float>(weapon.width) * rightLeft,static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y,weapon.width * scale, weapon.height *scale};
    DrawTexturePro(weapon,source,dest,origin,rotation,WHITE);

   //DrawRectangleLines(weaponCollisionRec.x,weaponCollisionRec.y,weaponCollisionRec.width,weaponCollisionRec.height,RED);
}

Vector2 Character::getScreenPos()
{
    return Vector2
    {
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * (float)width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * (float)height)
    };
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.0f)
    {
        setAlive(false);
    }
}
