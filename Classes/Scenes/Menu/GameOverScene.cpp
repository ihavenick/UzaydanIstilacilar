
#include "GameOverScene.h"
#include "../PlayScene.h"
#include "MainMenuScene.h"
#include "Core/GameManager.h"
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	return create();
}

bool GameOverScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

	auto backToMenuLabel = Label::createWithTTF("Yeniden Dene", "fonts/POP.ttf", 24);
	auto quitLabel = Label::createWithTTF("Çik", "fonts/POP.ttf", 24);

	auto retryItem = MenuItemLabel::create(
										backToMenuLabel,
										CC_CALLBACK_1(GameOverScene::menuRetryCallback, this));

	
		retryItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		const float x = origin.x + visibleSize.width / 2 - 50.f;
		const float y = origin.y + retryItem->getContentSize().height * 2;
		retryItem->setPosition(Vec2(x, y));
	
    auto exitItem = MenuItemLabel::create(
                                           quitLabel,
                                           CC_CALLBACK_1(GameOverScene::menuExitCallback, this));

   
		exitItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    const float x2 = origin.x + visibleSize.width / 2 + 50.f;
    const float y2 = origin.y + exitItem->getContentSize().height * 2;
        exitItem->setPosition(Vec2(x2,y2));
  

    auto menu = Menu::create(exitItem, retryItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);


    const auto gelenScore = GameManager::instance()->getScore();

    const auto lostLabel = Label::createWithTTF("Kaybettin!\nSkorun " + std::to_string(gelenScore) , "fonts/POP.ttf", 32);


	lostLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - lostLabel->getContentSize().height));

		
	this->addChild(lostLabel, 10);
	
	

    return true;
}

void GameOverScene::menuExitCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void GameOverScene::menuRetryCallback(Ref* pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInT::create(1.1, scene));
}


