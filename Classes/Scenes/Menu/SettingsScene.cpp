#include "SettingsScene.h"

#include "Core/DataManager.h"

USING_NS_CC;

Scene* SettingsPage::createScene()
{
    return create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}



bool SettingsPage::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();


    const auto label = Label::createWithTTF("Ayarlar", "fonts/POP.ttf", 34);
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
    

    MenuItemFont::setFontName("American Typewriter");
    MenuItemFont::setFontSize(18);
    const auto title1 = MenuItemFont::create("FPS Gostergesi");
    title1->setEnabled(false);
    MenuItemFont::setFontName( "fonts/POP.ttf" );
    auto item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(SettingsPage::fpsButtonCallback, this),
                                                                    MenuItemFont::create( "Goster" ),
                                                                    MenuItemFont::create( "Gosterme"),
                                                                    nullptr );

  


    MenuItemFont::setFontName("American Typewriter");
    MenuItemFont::setFontSize(18);
    const auto title2 = MenuItemFont::create("Kontroller");
    title2->setEnabled(false);
    MenuItemFont::setFontName( "fonts/POP.ttf" );
    auto item2 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(SettingsPage::controllButtonCallback, this),
                                                                    MenuItemFont::create( "1" ),
                                                                    MenuItemFont::create( "2"),
                                                                    nullptr );



    auto lBack = Label::createWithTTF( "Geri Don","fonts/POP.ttf",24);
    auto back = MenuItemLabel::create(lBack, CC_CALLBACK_1(SettingsPage::btMenuCallback, this) );
    

    
    //TODO SMALL SCREENS
    
    dataManager = DataManager::instance();
    
    item1->setSelectedIndex(dataManager->isShowFPSEnabled() ? 0 : 1);

    item2->setSelectedIndex(dataManager->getControlType()==2 ? 1 : 0);
    
    auto menu = Menu::create(title1, item1,
                             title2, item2, nullptr);
    menu->alignItemsInColumns(2, 2, 1, NULL);

    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    
    this->addChild(menu, 1);

    back->setPosition(visibleSize.width / 2 , origin.y + back->getContentSize().height);
   
    auto menu2 = Menu::create(back, nullptr);
    menu2->setPosition(Vec2(0,0));
    this->addChild(menu2, 1);
   
    

    return true;
}



void SettingsPage::btMenuCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void SettingsPage::controllButtonCallback(Ref* pSender)
{
    dataManager->setControllType(dataManager->getControlType() == 1 ? 2 : 1);
}

void SettingsPage::fpsButtonCallback(Ref* pSender)
{
    dataManager->setShowFps(dataManager->isShowFPSEnabled() == false ? true : false);
}
