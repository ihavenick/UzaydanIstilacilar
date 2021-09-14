#include "Object.h"
#include "DefaultValues.h"
#include "Objects/Bullet.h"
#include "Objects/Enemy.h"

USING_NS_CC;

Object* Object::create(int atag)
{
   if(atag==TAG_ENEMY)
   {
       //random for create powered enemies or weaker
       const int isPowerFull = RandomHelper::random_int(0, 1); //i hate this randomers. gives same numbers generally
       const auto e = new Enemy(isPowerFull);
       e->init();
       return e;
   }
   const auto b = new Bullet(25);
   b->init();
   return b;
}

bool Object::init()
{
     visibleSize = Director::getInstance()->getVisibleSize();
     origin = Director::getInstance()->getVisibleOrigin();

    //TODO test if this better here
    // auto rectBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    // rectBody->setContactTestBitmask(true);
    // this->setPhysicsBody(rectBody);

    return true;
}

void Object::reset()
{
}