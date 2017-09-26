#include "StartScene.h"
#include "GameScene.h"
#include "GameManager.h"

StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!BaseLayer::init())
		return false;

	setBackgroundImage(0);

	auto play = MenuItemImage::create("res/btnplaymain-sheet0.png", "res/btnplaymain-sheet1.png", CC_CALLBACK_1(StartScene::menuCallback, this));
	play->setPosition(size.width / 2, size.height * 0.3);
	auto menu = Menu::create(play, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);



	auto keypadListener = EventListenerKeyboard::create();
	keypadListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
			GameManager::getInstance()->exitGame();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keypadListener, this);


	return true;
}

void StartScene::menuCallback(Ref* sender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}