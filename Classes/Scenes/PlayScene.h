#ifndef __Play_SCENE_H__
#define __Play_SCENE_H__

#include "cocos2d.h"
class GameManager;
class PlayerController;

class PlayScene : public cocos2d::Scene
{
private:
    cocos2d::PhysicsWorld *	physicsWorld;
    bool gameLost;
    bool ignoreCol;


public:
    static Scene* createScene();
    
    virtual void update(float dt);
    virtual bool init();
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world);
    void setIgnoreCol(float dt);

    // touch event listener
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    void generateEnemies();

    void menuPauseCallback(Ref* pSender);
    void updateHealthUI();
    void showScore(int score);
    CREATE_FUNC(PlayScene);
    
};

#endif
