#include "Base.h"

#include "CCDirector.h"
#include "DefaultValues.h"

Base::Base()
{

    //This object is to detect enemies to collions with bottom of screen. yeah there is another way like checking y cordinate but doesnt want to check all enemies for its y cordinate
    
    const auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    initWithFile("base.png");
    const auto size = cocos2d::Size(visibleSize.width,1);
    setContentSize(size);
    const auto rectBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    rectBody->setContactTestBitmask(true);
    rectBody->setRotationEnable(false);
    rectBody->setDynamic(false);
    rectBody->setMass(2900.f);
    
    setTag(TAG_BASE);
    this->setPhysicsBody(rectBody);
}
