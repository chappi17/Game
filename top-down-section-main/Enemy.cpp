#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D texture_idle, Texture2D texture_run)
{
    worldPos = pos;
    texture = texture_idle;
    idle = texture_idle;
    run = texture_run;
    width = texture.width / maxframes;
    height = texture.height;
    speed = 3.5f;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->GetwolrdPos());
}

// vector that I need to implement

void Enemy::Tick(float deltaTime)
{
    if (!getAlive()) return;
    // the vector that Enemy to Character -> To_Taregt
    // a + b =c
    // b = c -a
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity)< radius) velocity ={};
    BaseCharacter::Tick(deltaTime);

    if(CheckCollisionRecs(target->GetCollisionRec(),GetCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }


}
