
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "cocos2d.h"


class Object : public cocos2d::Sprite
{
protected:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

public:
    static Object* create(int);

    virtual bool init();
    virtual void reset();
};

#endif 