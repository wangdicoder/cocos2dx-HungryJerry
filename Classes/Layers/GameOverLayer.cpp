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

	if (nTag == 1)
	{
		
	}
	else if (nTag == 2)
	{

	}
	else if (nTag == 3)
	{
		
	}
}