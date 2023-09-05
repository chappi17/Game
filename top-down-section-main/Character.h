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
    virtual Vector2 getScreenPos() override;
    Rectangle getweaponCollisionRec() {return weaponCollisionRec;}
    float getHealth() {return health;}
    void takeDamage(float damage);

private:
    int windowWidth ={};
    int windowHeight ={};
    Texture2D weapon {LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec = {};
    float health= 100.0f;
};

#endif