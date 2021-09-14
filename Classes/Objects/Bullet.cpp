#include "Bullet.h"

#include "DefaultValues.h"
#include "Core/GameManager.h"
#include "Core/ObjectPooler.h"


Bullet::Bullet(float damage)
{
    Sprite::initWithSpriteFrameName("bullet.png");
 
    auto rectBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    rectBody->setContactTestBitmask(true);
    this->setPhysicsBody(rectBody);
    
    Node::setTag(TAG_BULLET);
    inScene = false;
    damage_ = damage;
    setScale(0.5);
    //scheduleUpdate();
    
}


float Bullet::damage() const
{
    return damage_;
}

bool Bullet::getIsInScene() const
{
    return inScene;
}

void Bullet::reset()
{
    setRotation(0);
    inScene = true;
    scheduleUpdate();
}

bool Bullet::getisEnemyBullet() const
{
    return is_enemy_bullet_;
}

void Bullet::update(const float dt)
{
    if (!inScene)
        return;

    if (GameManager::instance()->getPaused())
    return;
    
    if (this->getPositionY() > visibleSize.height + origin.y + 10.f) 
    {
        remove();
        return;
    }
    if (this->getPositionY() <  origin.y - 10.f) 
    {
        remove();
        return;
    }
    
    if (is_enemy_bullet_)
        this->setPosition(this->getPosition().x, this->getPosition().y+ (dt * 800 * -1));
    else
        this->setPosition(this->getPosition().x, this->getPosition().y+ (dt * 800));
}

void Bullet::remove()
{
    inScene = false;
    setPosition(-100,-100); //dunno if its still necessary 
    //this->removeFromParent();
    GameManager::instance()->removeFromScene(this);
    ObjectPooler::getInstance()->returnAgent(this);
}

void Bullet::SetBulletType(bool is_enemy_bullet,int damage)
{
    is_enemy_bullet_ = is_enemy_bullet;
    damage_ = damage;
}
