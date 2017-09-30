#include "PauseLayer.h"
#include "StartScene.h"
#include "GameScene.h"
#include "GameManager.h"

PauseLayer::PauseLayer()
{
}


PauseLayer::~PauseLayer()
{
}

Scene* PauseLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseLayer::create();
	scene->addChild(layer);

	return scene;
}

bool PauseLayer::init()
{
	if (!BaseLayer::init())
		return false;

	auto bg = LayerColor::create(Color4B(0,0,0,200));
	this->addChild(bg);

	auto title = Sprite::create("res/bgpausa-sheet0.png");
	title->setPosition(size.width/2, size.height * 0.8);
	this->addChild(title);

	auto nextBtn = MenuItemImage::create("res/next_normal.png", "res/next_press.png", CC_CALLBACK_1(PauseLayer::menuCallback, this));
	nextBtn->setPosition(size.width/2, size.height * 0.4);
	nextBtn->setTag(0);
	auto menuBtn = MenuItemImage::create("res/btnmenusel-sheet0.png", "res/btnmenusel-sheet1.png", CC_CALLBACK_1(PauseLayer::menuCallback, this));
	menuBtn->setPosition(nextBtn->getPositionX() - nextBtn->getContentSize().width/2 - menuBtn->getContentSize().width/ 2, nextBtn->getPositionY() - nextBtn->getContentSize().height/2 + menuBtn->getContentSize().height/2);
	menuBtn->setTag(1);
	auto replayBtn = MenuItemImage::create("res/btnreset-sheet0.png", "res/btnreset-sheet1.png", CC_CALLBACK_1(PauseLayer::menuCallback, this));
	replayBtn->setPosition(nextBtn->getPositionX() + nextBtn->getContentSize().width / 2 + replayBtn->getContentSize().width / 2 * 1.46f, menuBtn->getPositionY());
	replayBtn->setTag(2);
	replayBtn->setScale(1.46f);
	auto menu = Menu::create(nextBtn, menuBtn, replayBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [](Touch *touch, Event *event){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void PauseLayer::menuCallback(Ref* sender)
{
	auto item = static_cast<MenuItemFont*>(sender);
	int nTag = item->getTag();

	Director::getInstance()->resume();
	if (nTag == 0)
	{
		this->removeFromParentAndCleanup(true);
	}
	else if (nTag == 1)
	{

	}
	else if (nTag == 2)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.8f, GameScene::createScene()));
	}
}