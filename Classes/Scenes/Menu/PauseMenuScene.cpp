
/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "PauseMenuScene.h"

#include "SettingsScene.h"
#include "Core/GameManager.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
    return create();
}

bool PauseMenu::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto origin = Director::getInstance()->getVisibleOrigin();


    const auto label = Label::createWithTTF("Duraklatildi", "fonts/POP.ttf", 34);


    label->setPosition(Vec2(origin.x + visibleSize.width/2,
        origin.y + visibleSize.height - label->getContentSize().height));


    this->addChild(label, 1);

    
    auto playLabel = Label::createWithTTF("Devam Et", "fonts/POP.ttf", 24);
    auto settingsLabel = Label::createWithTTF("Ayarlar", "fonts/POP.ttf", 24);
    auto quitLabel = Label::createWithTTF("Cikis", "fonts/POP.ttf", 24);
    
    auto menuPlay = MenuItemLabel::create(playLabel, CC_CALLBACK_1(PauseMenu::buttonResumeCallback, this));
    auto menuSettings = MenuItemLabel::create(settingsLabel, CC_CALLBACK_1(PauseMenu::buttonSettingsCallback, this));
    auto menuQuit = MenuItemLabel::create(quitLabel, CC_CALLBACK_1(PauseMenu::buttonQuitCallback, this));

    //TODO SMALL SCREENS
    
    auto previousY = origin.y + visibleSize.height - label->getContentSize().height -
        menuPlay->getContentSize().height - 30;
    
    menuPlay->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   previousY - 100));

    menuSettings->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   previousY - 200));
    menuQuit->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   previousY - 300));


    auto menu = Menu::create(menuPlay, menuSettings, menuQuit,  NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}



void PauseMenu::buttonResumeCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
    GameManager::instance()->pause(false);
}

void PauseMenu::buttonSettingsCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(TransitionFadeUp::create(0.8,
        SettingsPage::createScene()));
}
void PauseMenu::buttonQuitCallback(Ref* pSender)
{
    Director::getInstance()->end();
}