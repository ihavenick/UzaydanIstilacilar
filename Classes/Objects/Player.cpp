#include "Player.h"

#include "DefaultValues.h"
#include "cocostudio/SimpleAudioEngine.h"
#include "Core/GameManager.h"
#include "Core/ObjectPooler.h"


Player::Player()
{
    Sprite::initWithSpriteFrameName("player.png");

    f_Health = 100;
    setTag(TAG_PLAYER);
    

    auto rectBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    rectBody->setContactTestBitmask(true);
    this->setPhysicsBody(rectBody);
    //powerfullBullets = 0;
    poweredUp = false;
    setScale(0.5);
    scheduleOnce(CC_SCHEDULE_SELECTOR(Player::startShooting), 1);
}


void Player::startShooting(float dt)
{
    schedule(CC_SCHEDULE_SELECTOR(Player::shoot), FIRE_RATE, CC_REPEAT_FOREVER, 1);
    
}

void Player::reset()
{
    this->f_Health = 100;
    //powerfullBullets = 0;
    poweredUp = false;
    scheduleOnce(CC_SCHEDULE_SELECTOR(Player::startShooting), 1);
}

int Player::getHealth()
{
    return f_Health;
}

void Player::onHit(Bullet* oBullet)
{
    if (f_Health>0)  //not to die again
    {
        this->f_Health -= oBullet->damage();
        
        if (f_Health <= 0)  //gameover if health is 0
            GameManager::instance()->switchScene(3);
    }
}

void Player::shoot(float dt)
{
    if (f_Health>0 && !GameManager::instance()->getPaused())  //shoot if not paused and health is bellow 0
    {
        const auto gelenBullet = (Bullet*)ObjectPooler::getInstance()->getAgent(TAG_BULLET);
        if ( gelenBullet == nullptr) {
            printf("get bullet error");
        }
        else {
            if (gelenBullet->getIsInScene())
            {
                // what the ? this bullet is allready in scene why its in this pool ?
                shoot(1);
                return;
            }
            //set bullet damage and its type
            gelenBullet->SetBulletType(false,poweredUp ? 100 : 25);
            gelenBullet->setColor(cocos2d::Color3B( 255,poweredUp ? 0 : 255,poweredUp ? 0 : 255));
            
            // if (powerfullBullets>0)   //decrease powerfull bullet count if morethan 0            I read email wrong and thought its 3 bullet but its 3 seconds soo thats stays to let you look to it
            //     powerfullBullets--;
            gelenBullet->setPositionX(this->getPositionX()); 
            gelenBullet->setPositionY(this->getPositionY() + this->getContentSize().height - 1);

           
            GameManager::instance()->spawnInScene(gelenBullet);
            gelenBullet->reset();

            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            audio->playEffect("ates.mp3", false, 1.0f, 1.0f, 0.2f);
        }
    }
}
//add powerfull bullet count (scheduler requires a float parameter. dunno why ask them
void Player::setPoweredBullets(float counnt)
{
    //so i read email wrong and made it bullet count but i will fix it someway. I dont gonna delete old one to let you see
    //powerfullBullets += counnt;

    if (poweredUp)
    {
        setColor(cocos2d::Color3B(255,255,255));
        poweredUp = false;
    }
    else
    {
        poweredUp = true;
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playEffect("superguc.mp3", false, 1.0f, 1.0f, 0.2f);
        setColor(cocos2d::Color3B(255,0,0));
        scheduleOnce(CC_SCHEDULE_SELECTOR(Player::setPoweredBullets), 3);
    }
}
