#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D texture_idle, Texture2D texture_run);
    void SetTarget(Character* Character) { target =Character; }

    virtual void Tick(float deltaTime) override;
private:
    Character* target;
};