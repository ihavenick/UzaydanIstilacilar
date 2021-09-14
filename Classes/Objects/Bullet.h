#pragma once
#include "Core/Object.h"


class Bullet : public Object
{

private:
    float damage_;
    bool inScene;
    bool is_enemy_bullet_;

public:
    Bullet(float damage);
    void SetBulletType(bool is_enemy_bullet , int);
    float damage() const;
    bool getIsInScene() const;
    void reset();
    bool getisEnemyBullet() const;
    virtual void update(float dt);
    void remove();
};
