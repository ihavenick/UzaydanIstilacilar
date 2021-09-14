#pragma once

#include "cocos2d.h"

class Player;

class PlayerController
{
private:
    static PlayerController* _instance;
    cocos2d::Size shipSize;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    bool touchBegan;
    float ftouchX, ftouchY;
    Player* player;
    int controllType;

public:
    static PlayerController* instance();
    PlayerController();
    void reset();
    ~PlayerController();
    void initialize(cocos2d::Scene* gelen);
    void givePoweredUpBullets(int count) const;
    void setControllType(int type);
    int getPlayerHealth() const;
    void update(float dt);

    void onTouchBegan(float tX);
    void onTouchMoved(float tX);
    void onTouchEnded(float tX);
    
};
