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