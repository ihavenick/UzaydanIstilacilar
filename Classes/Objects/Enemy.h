#pragma once
#include "Core/Object.h"


class Bullet;

class Enemy : public Object
{
protected:
     int f_FullHealth;
     int f_Health;
    bool isStrongEnemy;
    bool isMovedRight;
     cocos2d::Vector<cocos2d::SpriteFrame*> _frames;

public:
    Enemy(int type);
     void animate();
     void shoot(float dt);
    virtual void onHit(Bullet* bHit);
    virtual void reset();
    void move();
    bool isDead;

private:
    void updateHealthLabel() const;
};
