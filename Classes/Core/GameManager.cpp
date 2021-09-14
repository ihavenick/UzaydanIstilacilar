
#include "GameManager.h"

#include "DataManager.h"
#include "ObjectPooler.h"
#include "PlayerController.h"
#include "Scenes/Menu/GameOverScene.h"
#include "Scenes/Menu/PauseMenuScene.h"

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::instance() {
    if (_instance == nullptr) {
        _instance = new GameManager();
    }
    return _instance;
}

void GameManager::succsesfulHit()
{
    hitCounter++;
    if (hitCounter >= 5)
    {
        //if player manage to shoot enemy successfully 5 time give them 3 powerfull bullets
        hitCounter = 0; // FIXXED   couldnt find a way to implement it. powerfull bullets counts hits too maybe adding a bool to not register it better way ? TODO find way to not count powerfull bullets  FIXXED


        //soo i read email wrong. its 3 secs not 3 bullets :D
        PlayerController::instance()->givePoweredUpBullets(3);
    }
}

void GameManager::setEnemySpeed(const float spd)
{
    if (speed <=0.4f)
    return;
    speed += spd;
}


float GameManager::getEnemySpeed() const
{
    return speed;
}


int GameManager::getScore() const
{
    return score;
}


void GameManager::reset()
{
     speed = 1.f;
     score = 0;
     isPaused = false;
     hitCounter = 0;
     enemyCount = 0;
    PlayerController::instance()->reset();
    ObjectPooler::getInstance()->reset();
}

void GameManager::switchScene(int sceneNum)
{
    //dunno why i didnt added other scenes maybe because its not necessary or i am lazy
    switch (sceneNum)
    {
        cocos2d::Scene* scene;
    case 2 :
            
            scene = PauseMenu::createScene();
            cocos2d::Director::getInstance()->pushScene(cocos2d::TransitionFadeUp::create(0.8, scene));
        break;
        
        case 3 :
            if (DataManager::instance()->getHighScore()<score)
            {
                DataManager::instance()->setHighScore(score);
            }
            playScene->stopAllActions();
            scene = GameOverScene::createScene();
            reset();
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5, scene, cocos2d::Color3B(224, 30, 30)));
        
        break;
        default: ;
    }
}

void GameManager::addScore(const int s)
{
    score += s;
    playScene->showScore(score);
}

GameManager::GameManager()
{
    speed = 1.f;
    enemyCount=0;
    score = 0;
    hitCounter= 0;
    isPaused =false;
    PlayerController::instance()->setControllType(DataManager::instance()->getControlType());
}

GameManager::~GameManager()   //Dispose
{
    playScene->cleanup();
}

bool GameManager::getPaused() const
{
    return isPaused;
}

void GameManager::setEnemyCount(int i)
{
    enemyCount+=i;
    if (enemyCount==0)     //SETS ENEMY COUNT IF THERE IS NO ENEMY LEFT REGENERATES THEM 
    {
        setEnemySpeed(-0.25f);
        playScene->setIgnoreCol(1); //disables collisions for 1.5 sec to not get bugged. BUG
        playScene->generateEnemies();
    }
}

void GameManager::setGameScene(PlayScene* playScene)
{
    this->playScene = playScene;
}

void GameManager::pause(bool bPause)
{
    isPaused = bPause;
    bPause ? switchScene(2) : PlayerController::instance()->setControllType(DataManager::instance()->getControlType());
}

void GameManager::removeFromScene(cocos2d::Node* n)
{
    playScene->removeChild(n);
}

void GameManager::spawnInScene(cocos2d::Node* n)
{
    playScene->addChild(n);        
}