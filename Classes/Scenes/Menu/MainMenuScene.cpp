#include "MainMenuScene.h"

#include "SettingsScene.h"
#include "Scenes/PlayScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool MainMenu::init()
{
    
    if ( !Scene::init() )
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto origin = Director::getInstance()->getVisibleOrigin();


    const auto label = Label::createWithTTF("UZAYDAN\n ISTILACILAR", "fonts/POP.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/POP.ttf'");
    }
    else
    {

        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));


        this->addChild(label, 1);
    }

    
    auto playLabel = Label::createWithTTF("Oyna", "fonts/POP.ttf", 24);
    auto settingsLabel = Label::createWithTTF("Ayarlar", "fonts/POP.ttf", 24);
    auto quitLabel = Label::createWithTTF("Cikis", "fonts/POP.ttf", 24);
    
    auto menuPlay = MenuItemLabel::create(playLabel, CC_CALLBACK_1(MainMenu::menuPlayCallback, this));
    auto menuSettings = MenuItemLabel::create(settingsLabel, CC_CALLBACK_1(MainMenu::menuSettingsCallback, this));
    auto menuQuit = MenuItemLabel::create(quitLabel, CC_CALLBACK_1(MainMenu::menuQuitCallback, this));

    //TODO SMALL SCREENS
    
    auto previousY = origin.y + visibleSize.height - label->getContentSize().height - menuPlay->getContentSize().height - 30;
    
    menuPlay->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   previousY - 100));

    menuSettings->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   previousY - 200));
    menuQuit->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   previousY - 300));

    const auto score = Label::createWithTTF("High Score :\n " +std::to_string(DataManager::instance()->getHighScore()), "fonts/POP.ttf", 26);
    
    score->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    score->setPosition(score->getWidth(),visibleSize.height - score->getHeight());
    this->addChild(score);
    
    auto menu = Menu::create(menuPlay, menuSettings, menuQuit,  NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    return true;
}


void MainMenu::menuQuitCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void MainMenu::menuPlayCallback(Ref* pSender)
{
    const auto scene = PlayScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(1.1, scene));
}
void MainMenu::menuSettingsCallback(Ref* pSender)
{
    const auto scene = SettingsPage::createScene();
    Director::getInstance()->pushScene(TransitionFadeUp::create(0.8, scene));
}