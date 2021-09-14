#include "PlayerController.h"

#include "GameManager.h"
#include "Objects/Player.h"


USING_NS_CC;

PlayerController* PlayerController::_instance = nullptr;

PlayerController* PlayerController::instance()
{
    if (_instance == nullptr) {
        _instance = new PlayerController();
    }
    return _instance;
}

PlayerController::PlayerController()
{
    player = new Player();
    touchBegan = false;
}

void PlayerController::reset()
{
    DeleteObject(player);
    player = new Player();
    touchBegan = false;
}

void PlayerController::initialize(Scene* gelen)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    shipSize = player->getContentSize();
    player->setPosition(visibleSize.width / 2 + origin.x, shipSize.height * 0.2 + origin.y);

    GameManager::instance()->spawnInScene(player);
    //gelen->addChild(player);
}

void PlayerController::givePoweredUpBullets(int count) const
{
    //not count its secconds i read email wrong
    player->setPoweredBullets(count);
}

void PlayerController::setControllType(int type)
{
    controllType = type;
}

int PlayerController::getPlayerHealth() const
{
    return player->getHealth();
}

void PlayerController::update(float dt)
{
    
    if (touchBegan)
    {
        if(controllType == 1)
        {
            float curx = player->getPositionX();
            
            if (ftouchX < (visibleSize.width/2))
            {
                if (curx> origin.x + shipSize.width )
                {
                    player->setPositionX(curx - 5);
                }
                
            }
            else
            {
                if (curx < visibleSize.width - shipSize.width )
                {
                    player->setPositionX(curx + 5);
                }
                
            }
        }
        else
        {
            auto limit = 20.f;
            float curx = player->getPositionX();
            if (curx + limit <= std::min(ftouchX, visibleSize.width - shipSize.width / 2))
            {
                player->setPositionX(curx + limit);
            }
            else if (curx - 10.f >= std::max(ftouchX, shipSize.width / 2))
            {
                player->setPositionX(curx - limit);
            }
        }
       
    }
}


void PlayerController::onTouchBegan(float tX)
{
    touchBegan = true;
    ftouchX = tX;
}

void PlayerController::onTouchMoved(float tX)
{
    ftouchX = tX;
}

void PlayerController::onTouchEnded(float tX)
{
    ftouchX = tX;
    touchBegan = false;
}

PlayerController::~PlayerController()
{
    delete player;
}