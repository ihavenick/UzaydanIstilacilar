#include "Enemy.h"

#include "Bullet.h"
#include "DefaultValues.h"
#include "cocostudio/SimpleAudioEngine.h"
#include "Core/GameManager.h"
#include "Core/ObjectPooler.h"

USING_NS_CC;

Enemy::Enemy(int type) 
{
    isDead = false;

    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    
    
    //if int 0 strong enemy
    if (type == 0)
    {
        Sprite::initWithSpriteFrameName("uzayli1_1.png");
        f_FullHealth = 100;
        _frames.pushBack(cache->getSpriteFrameByName("uzayli1_1.png"));
        _frames.pushBack(cache->getSpriteFrameByName("uzayli1_2.png"));
        

    }
    else // else weaker enemy
    {
        Sprite::initWithSpriteFrameName("uzayli2_1.png");
        f_FullHealth = 50;
        _frames.pushBack(cache->getSpriteFrameByName("uzayli2_1.png"));
        _frames.pushBack(cache->getSpriteFrameByName("uzayli2_2.png"));
    }


    f_Health = f_FullHealth;
    setTag(TAG_ENEMY);

    Label* l_health = Label::createWithTTF(std::to_string(f_Health), "fonts/POP.ttf", 46);
    l_health->setName("LabelHealth");
    
    l_health->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    l_health->setPosition(35,-65);
    this->addChild(l_health);

    //int randShoot = RandomHelper::random_int(7,15);
    //schedule(CC_SCHEDULE_SELECTOR(Enemy::shoot), randShoot, 0, 2);

    auto rectBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
    rectBody->setContactTestBitmask(true);
    rectBody->setRotationEnable(false);
    rectBody->setDynamic(false);
    rectBody->setMass(200.f);
    this->setPhysicsBody(rectBody);
    

    //runAction(RepeatForever::create(animateAction));

    //schedule(CC_SCHEDULE_SELECTOR(Enemy::move), 2, CC_REPEAT_FOREVER, 2);
    


    animate();
    setScale(0.25f);
}

void Enemy::animate()
{
    auto speed = GameManager::instance()->getEnemySpeed();
    
    const auto _anim = Animation::createWithSpriteFrames(_frames, speed);
    _anim->retain();

    const auto animateAction = Animate::create(_anim);
    
     //not that much "speed" but dunno
    const auto moveVertical = CallFunc::create([this](){
        move();
    });

    const auto moveHorizantal = CallFunc::create([this](){
        setPosition(getPosition().x, getPosition().y - 30 );
    });

    
    const auto seq = Sequence::create(animateAction, moveVertical, animateAction, moveVertical, moveHorizantal, nullptr);
    
    runAction(RepeatForever::create(seq));
    
}


void Enemy::updateHealthLabel() const
{
    const auto gelen = this->getChildByName("LabelHealth");
    const auto lHealth = static_cast<Label*>(gelen);
    lHealth->setString(std::to_string(f_Health));
}

void Enemy::reset()
{
    isDead = false;
    animate();
    this->f_Health = this->f_FullHealth;
    updateHealthLabel();
    
}

void Enemy::move()
{
    if (isMovedRight == true)
    {
        setPosition(getPosition().x- 10, getPosition().y );
        isMovedRight = false;
        
    }
    else
    {
        setPosition(getPosition().x + 10, getPosition().y);
        isMovedRight = true;
    }

    const auto a = RandomHelper::random_int(0,100);
        
    if (a>95)
        shoot(1);


    if (getPosition().x > visibleSize.width ||
        getPosition().x < origin.x||
        getPosition().y < origin.y ||
        getPosition().y > visibleSize.height + 170)
    {
        isDead = true;
        GameManager::instance()->setEnemyCount(-1);
        GameManager::instance()->removeFromScene(this);
        removeFromParent();
        ObjectPooler::getInstance()->returnAgent(this);
    }
}

void Enemy::onHit(Bullet* oBullet)
{
    this->f_Health -= oBullet->damage();
    
    if (oBullet->damage()!=100)                    //Dont count powerfull damage hit for hitcounter to give them easier powerfull bullets
        GameManager::instance()->succsesfulHit();
    
    if (f_Health <= 0)
    {
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playEffect("patlama.mp3", false, 1.0f, 1.0f, 0.2f);
        isDead = true;
        auto gameManager = GameManager::instance();
        gameManager->setEnemyCount(-1);
        gameManager->removeFromScene(this);
        removeFromParent();
        ObjectPooler::getInstance()->returnAgent(this);

        if (isStrongEnemy)
            GameManager::instance()->addScore(50);
        else
            GameManager::instance()->addScore(25);
        
        return;
    }
    updateHealthLabel();
}

void Enemy::shoot(float dt)
{
    if (isDead)
        return;
    
    auto gelen_bullet = static_cast<Bullet*>(ObjectPooler::getInstance()->getAgent(TAG_BULLET));
    
    if (gelen_bullet == nullptr) {
        printf("cant shoot, Get bullet error");
        return;
    }
    if (gelen_bullet->getIsInScene())
    {
        printf("bullet is allready in scene ??? how");
        return;
    }
        
    gelen_bullet->SetBulletType(true,25);
    gelen_bullet->setPosition(this->getPositionX(),
                             this->getPositionY() - this->getContentSize().height -10);

    gelen_bullet->setColor(cocos2d::Color3B(0,255,0));
    GameManager::instance()->spawnInScene(gelen_bullet);
    gelen_bullet->reset();
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("ates-ters.mp3", false, 1.0f, 1.0f, 0.2f);
  
}
