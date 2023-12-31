
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();

    Vector2 GetwolrdPos() { return worldPos; }
    virtual void Tick(float deltaTime);
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() {return alive;}
    bool setAlive(bool isalive) {return alive = isalive;}

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    // chracter to screen = screen's x,y cordination
    Vector2 screenPos = {};
    // {0,0} that window's start point (맵이 움직이는거니까 월드 포즈가 메인)
    Vector2 worldPos = {};
    // 1 : facing right  -1: facing left
    float rightLeft = 1.0f;
    // animation variables
    float runningTime = 0;
    int frame = 0;
    const int maxframes = 6;
    // if updateTime is smaller -> fast
    const float updateTime = 1.0f / 24.0f;
    float speed = 4.0f;
    float width = 0;
    float height = 0;
    Vector2 WorldPostLastFrame = {};
    float scale = 4.0f;
    Vector2 velocity = {};

private:
    bool alive = true;
};

#endif