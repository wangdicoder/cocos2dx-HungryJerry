#include "GameOverLayer.h"
#include "StartScene.h"
#include "GameScene.h"
#include "GameManager.h"

GameOverLayer::GameOverLayer()
{
}


GameOverLayer::~GameOverLayer()
{
}

Scene* GameOverLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverLayer::create();
	scene->addChild(layer);

	return scene;
}

bool GameOverLayer::init()
{
	if (!BaseLayer::init())
		return false;

	auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 180));
	this->addChild(colorLayer);

	auto title = Sprite::create("res/bgcomplete-sheet0.png");
	title->setPosition(size.width/2, size.height * 0.8);
	this->addChild(title);


	auto nextBtn = MenuItemImage::create("res/next_normal.png", "res/next_press.png", CC_CALLBACK_1(GameOverLayer::menuCallback, this));
	nextBtn->setPosition(size.width - nextBtn->getContentSize().width / 2 * 0.5f - 25, nextBtn->getContentSize().height / 2 * 0.5f + 15);
	nextBtn->setScale(0.5f);
	nextBtn->setTag(0);
	auto menuBtn = MenuItemImage::create("res/btnmenusel-sheet0.png", "res/btnmenusel-sheet1.png", CC_CALLBACK_1(GameOverLayer::menuCallback, this));
	menuBtn->setPosition(menuBtn->getContentSize().width/2 + 10, menuBtn->getContentSize().height/2 + 15);
	menuBtn->setTag(1);
	auto replayBtn = MenuItemImage::create("res/btnreset-sheet0.png", "res/btnreset-sheet1.png", CC_CALLBACK_1(GameOverLayer::menuCallback, this));
	replayBtn->setPosition(replayBtn->getContentSize().width / 2 * (menuBtn->getContentSize().width / replayBtn->getContentSize().width) + 10, menuBtn->getPositionY() + replayBtn->getContentSize().height * (menuBtn->getContentSize().width / replayBtn->getContentSize().width) + 15);
	replayBtn->setScale(menuBtn->getContentSize().width / replayBtn->getContentSize().width);
	replayBtn->setTag(2);
	auto menu = Menu::create(nextBtn, menuBtn, replayBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);


	auto starRate = Sprite::create("res/complete_stars-sheet0.png");
	starRate->setPosition(size.width/2, size.height*0.45);
	this->addChild(starRate);

	auto scoreBg = Sprite::create("res/bgscorecomplete-sheet0.png");
	scoreBg->setPosition(size.width/2, scoreBg->getContentSize().height /2 + 25);
	this->addChild(scoreBg);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [](Touch *touch, Event *event){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void GameOverLayer::menuCallback(Ref* sender)
{
	auto item = static_cast<MenuItemFont*>(sender);
	int nTag = item->getTag();

	if (nTag == 0)
	{
		
	}
	else if (nTag == 1)
	{

	}
	else if (nTag == 2)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.8f, GameScene::createScene()));
	}
}