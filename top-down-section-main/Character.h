#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    ~Character();

    virtual void Tick(float deltaTime) override;
    Vector2 GetScreenPos() {return screenPos;}

private:
};

#endif