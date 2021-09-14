#include "PlayScene.h"

#include "DefaultValues.h"
#include "cocostudio/SimpleAudioEngine.h"
#include "Objects/Bullet.h"
#include "Objects/Enemy.h"
#include "Core/GameManager.h"
#include "Core/ObjectPooler.h"
#include "Objects/Player.h"
#include "Core/PlayerController.h"
#include "Objects/Base.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
    const auto physicsScene = createWithPhysics();
    //physicsScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    physicsScene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    const auto main = create();
    main->SetPhysicsWorld(physicsScene->getPhysicsWorld());

    physicsScene->addChild(main);
    return physicsScene;
}


void PlayScene::SetPhysicsWorld(cocos2d::PhysicsWorld* world)
{
    physicsWorld = world; 
}

void PlayScene::setIgnoreCol(float dt)
{
    if (ignoreCol==false)
    {
        ignoreCol = true;
        scheduleOnce(CC_SCHEDULE_SELECTOR(PlayScene::setIgnoreCol), 1.5); //re activate it after 1.5 sec
    }
    else
        ignoreCol=false;
}


bool PlayScene::init()
{
    ignoreCol=false;
    gameLost = false;
    if ( !Scene::init() )
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto origin = Director::getInstance()->getVisibleOrigin();


    const auto sprite = Sprite::create("back.png");
    const auto sprite2 = Sprite::create("stars.png");
    if (sprite == nullptr || sprite2 == nullptr) {
        printf("'back.png or stars.png' is missing.");
    }
    else
    {
        //TODO FIND WAY TO GET THIS WORKING
        const auto paraNode = ParallaxNode::create();
        
        paraNode->addChild(sprite, -1, Vec2(0.4f,0.5f), Vec2::ZERO);
        paraNode->addChild(sprite2, 1, Vec2(2.2f,1.0f), Vec2(500,+200) );
       
        this->addChild(paraNode, 0);
    }
    
    auto pauseMenuSprite = Sprite::createWithSpriteFrameName("pause.png");
    auto pauseButton = MenuItemSprite::create(pauseMenuSprite, pauseMenuSprite, nullptr,
                                              CC_CALLBACK_1(PlayScene::menuPauseCallback, this));
    pauseButton->setScale(0.7);

    const float px = origin.x + visibleSize.width - pauseButton->getContentSize().width/2;
    const float py = origin.y + pauseButton->getContentSize().height/2;
    pauseButton->setPosition(Vec2(px,py));

    const auto base = new Base();
    base->setPosition(visibleSize.width/2,0);
    this->addChild(base);

    const auto score = Label::createWithTTF("Skor :\n " +std::to_string(0), "fonts/POP.ttf", 26);
    score->setName("score");
    
    score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    score->setPosition(score->getWidth(),visibleSize.height - score->getHeight());
    this->addChild(score);

    const auto health = Label::createWithTTF("Can :\n " +std::to_string(100), "fonts/POP.ttf", 26);
    health->setName("health");
    
    health->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    health->setPosition(visibleSize.width - health->getWidth(),visibleSize.height - health->getHeight());
    this->addChild(health);
    
    auto menu = Menu::create(pauseButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    const auto gameManager = GameManager::instance();
    const auto playerController = PlayerController::instance();
    
    gameManager->setGameScene(this);
    playerController->initialize(this);
    

    //           event handlers
    const auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    //          physics handlers
    const auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    generateEnemies();

    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->setEffectsVolume(0.5);

    
    scheduleUpdate();
    return true;
}


void PlayScene::menuPauseCallback(Ref* pSender)
{
    GameManager::instance()->pause(true);
}

void PlayScene::updateHealthUI()
{
    const auto gelen = this->getChildByName("health");
    const auto healthLabel = static_cast<Label*>(gelen);
    const auto healt = PlayerController::instance()->getPlayerHealth();
    healthLabel->setString("Can :\n " + std::to_string(healt));
}

void PlayScene::showScore(int score)
{
    const auto gelen = this->getChildByName("score");
    const auto scoreLabel = static_cast<Label*>(gelen);
    scoreLabel->setString("Skor :\n " + std::to_string(score));
}

void PlayScene::update(float dt)
{
    if (GameManager::instance()->getPaused())
    return;
    
    PlayerController::instance()->update(dt);
}

bool PlayScene::onTouchBegan(Touch *touch, Event *event)
{
    PlayerController::instance()->onTouchBegan( touch->getLocation().x);
    return true;
}

bool PlayScene::onTouchMoved(Touch *touch, Event *event)
{
    PlayerController::instance()->onTouchMoved(touch->getLocation().x);
    return true;
}

bool PlayScene::onTouchEnded(Touch *touch, Event *event)
{
    PlayerController::instance()->onTouchEnded(touch->getLocation().x);
    return true;
}

bool PlayScene::onContactBegin(PhysicsContact &contact)
{
    if (gameLost)
    return false;

    const auto col1 = contact.getShapeA()->getBody()->getNode();
    const auto col2 = contact.getShapeB()->getBody()->getNode();

    const int tagA = col1->getTag();
    const int tagB = col2->getTag();
	
    if ((tagA == TAG_PLAYER && tagB == TAG_ENEMY) || 
        (tagB == TAG_PLAYER && tagA == TAG_ENEMY)) {
        //if enemy col with player , its gameover

        GameManager::instance()->switchScene(3);
        
        return true;
        }
    if ((tagA == TAG_BULLET && tagB == TAG_ENEMY) || 
        (tagB == TAG_BULLET && tagA == TAG_ENEMY))
    {
        //if bullet col with enemy , register hit and add bullet to objectpool
        const auto bullet = static_cast<Bullet*>(tagA == TAG_BULLET ? col1 : col2);
        const auto enemy = static_cast<Enemy*>(tagA == TAG_ENEMY ? col1 : col2);

        //if its enemy bullet do nothing and return
        if (bullet->getisEnemyBullet())
            return false;
        bullet->remove();
        enemy->onHit(bullet);
        
        return true;
    }

    if ((tagA == TAG_BULLET && tagB == TAG_PLAYER) || 
      (tagB == TAG_BULLET && tagA == TAG_PLAYER))
    {
        //if bullet collision with player , register hit and add bullet to pool

        const auto player = static_cast<Player*>(tagA == TAG_PLAYER ? col1 : col2);
        const auto bullet = static_cast<Bullet*>(tagA == TAG_BULLET ? col1 : col2);

        bullet->remove();
        player->onHit(bullet);
        updateHealthUI();
        return true;
    }

    if ((tagA == TAG_ENEMY && tagB == TAG_BASE) || 
          (tagB == TAG_ENEMY && tagA == TAG_BASE))
    {
        //there is one sec bug in REgenerating enemies soo thats why it has to ignored for 1 sec
        if(ignoreCol)
            return false;
        
        gameLost = true;  // if there is more than one enemy collision with base dont register it (acts like fuse)
        //if enemy hit base its GG
        GameManager::instance()->switchScene(3);
        return true;
    }

    if ((tagA == TAG_BULLET && tagB == TAG_BASE) || 
        (tagB == TAG_BULLET && tagA == TAG_BASE))
    {
        //remove bullet if its collision with base
        const auto bullet = static_cast<Bullet*>(tagA == TAG_BULLET ? col1 : col2);
        bullet->remove();
        return true;
    }
    
    
    if (tagA == TAG_BULLET && tagB == TAG_BULLET)
    {
        //bullet to bullet collision to remove themselfs like in original game

        const auto bullet2 = static_cast<Bullet*>(col1);
        const auto bullet = static_cast<Bullet*>(col2);

        //Checking if one of them is enemy bullet
        if (bullet->getisEnemyBullet() && !bullet2->getisEnemyBullet() ||   
            !bullet->getisEnemyBullet() && bullet2->getisEnemyBullet() )
        {
            bullet->remove();
            bullet2->remove();
        }
        return true;
    }
    
    return false;
}

void PlayScene::generateEnemies()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto origin = Director::getInstance()->getVisibleOrigin();

    //creating enemy for getting its size. yeah its not great way but it makes it %100 accurate :D
    const auto e = new Enemy(1);
    
    const auto marginx = 10.f;
    const auto enemywidth = e->getContentSize().width;

    const float deltavalue = visibleSize.width - marginx / 2.f;
    const int colonenemycount = (deltavalue / enemywidth + 1) / 1.2f;
    
    int enemyCount = 0;
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < colonenemycount; i++)
        {
            const auto enemy = static_cast<Enemy*>(ObjectPooler::getInstance()->getAgent(TAG_ENEMY));
            if (enemy == nullptr) 
                cocos2d::log("error getting enemy");
            else {
                enemyCount++;
                enemy->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
                enemy->setPosition(Vec2(  (visibleSize.width/4) +(visibleSize.width -deltavalue) + (marginx + 50) * i, 
                                          visibleSize.height +origin.y + 50 * j));
                this->addChild(enemy, 1);
            }
        }
    GameManager::instance()->setEnemyCount(+enemyCount);   //setting enemy count to track enemies and not to check its count on update to regenerate enemies
    DeleteObject(e); //deleting enemy object because dunno if this engine has garbage collector
}