#pragma once
#include "Bullet.h"
#include "2d/CCSprite.h"

class Bullet;


class Player : public cocos2d::Sprite
{
private:
//int powerfullBullets;
    bool poweredUp;

protected:
    int f_Health;

public:
    
    Player();

virtual void onHit(Bullet* bHit);
    void shoot(float);
    void setPoweredBullets(float counnt);
void startShooting(float dt);
    virtual void reset();
int getHealth();
};
