#pragma once
#include "CCUserDefault.h"

class DataManager
{
private:
    cocos2d::UserDefault* userData;
    static DataManager* _instance;
public:
    DataManager();
    bool isShowFPSEnabled() const;
    int getControlType() const;
    void setControllType(int type) const;
    void setShowFps(bool enabled) const;
    void setHighScore(int score) const;
    int getHighScore() const;
    ~DataManager();
    static DataManager* instance();
};
