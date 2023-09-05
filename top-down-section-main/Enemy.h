#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D texture_idle, Texture2D texture_run);
    void SetTarget(Character* Character) { target =Character; }
    virtual Vector2 getScreenPos() override;

    virtual void Tick(float deltaTime) override;
private:
    Character* target;
    float damagePerSec = 10.0f;
    float radius =25.0f;
};