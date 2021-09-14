#include "DataManager.h"
#include "CCDirector.h"
#include "CCUserDefault.h"

DataManager* DataManager::_instance = nullptr;

DataManager* DataManager::instance() {
    if (_instance == nullptr) {
        _instance = new DataManager();
    }
    return _instance;
}


//Access data and acts like data layer between other things :D
DataManager::DataManager()
{
    userData = cocos2d::UserDefault::getInstance();
}

bool DataManager::isShowFPSEnabled() const
{
    return userData->getBoolForKey("showFPS");
}

int DataManager::getControlType() const
{
    return userData->getIntegerForKey("ControllType");
}

void DataManager::setControllType(int type) const
{
    userData->setIntegerForKey("ControllType",type);
}

void DataManager::setShowFps(bool enabled) const
{
    userData->setBoolForKey("showFPS",enabled);
    cocos2d::Director::getInstance()->setDisplayStats(enabled);
}

void DataManager::setHighScore(int score) const
{
    userData->setIntegerForKey("HighScore",score);
}

int DataManager::getHighScore() const
{
    return userData->getIntegerForKey("HighScore");
}
