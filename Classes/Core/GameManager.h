#pragma once
#include "cocos2d.h"
#include "Scenes/PlayScene.h"

class GameManager
{
private:
    static GameManager* _instance;
    PlayScene* playScene;
    int score;
    bool isPaused;
    int hitCounter;
    float speed;
    int enemyCount;

public:
    GameManager();
    ~GameManager();
    bool getPaused() const;
    void setEnemyCount(int i);
    static GameManager* instance();
    void succsesfulHit();
    void setEnemySpeed(float spd);
    float getEnemySpeed() const;
    int getScore() const;
    void reset();
    void switchScene(int sceneNum);
    void addScore(int score);
    virtual void setGameScene(PlayScene* playScene);
    void pause(bool bPause);
    void removeFromScene(cocos2d::Node* n);
    void spawnInScene(cocos2d::Node* n);
    void quit();
};

