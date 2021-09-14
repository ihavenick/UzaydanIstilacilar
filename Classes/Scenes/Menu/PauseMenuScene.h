#ifndef __PauseMenu_SCENE_H__
#define __PauseMenu_SCENE_H__

#include "cocos2d.h"

class PauseMenu : public cocos2d::Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    void buttonResumeCallback(cocos2d::Ref* pSender);
    void buttonSettingsCallback(cocos2d::Ref* pSender);
    void buttonQuitCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(PauseMenu);
};

#endif
