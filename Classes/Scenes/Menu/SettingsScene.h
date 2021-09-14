#ifndef __SettingsPage_SCENE_H__
#define __SettingsPage_SCENE_H__

#include "cocos2d.h"
#include "Core/DataManager.h"

class SettingsPage : public cocos2d::Scene
{
private:
    DataManager* dataManager;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void btMenuCallback(cocos2d::Ref* pSender);
    void controllButtonCallback(cocos2d::Ref* pSender);
    void fpsButtonCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(SettingsPage);
};

#endif
