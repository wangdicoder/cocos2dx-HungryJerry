#include "StartScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "SelectScene.h"

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
	GameManager::getInstance()->createAnimation();
	
	auto leftEar = Sprite::create("res/menu_rata_oreja-sheet0.png");
	leftEar->setPosition(size.width*0.437, size.height*0.4);
	this->addChild(leftEar,1);

	auto rightEar = Sprite::create("res/menu_rata_oreja-sheet0.png");
	rightEar->setPosition(size.width*0.56, leftEar->getPositionY());
	this->addChild(rightEar,1);
	rightEar->setFlippedX(true);

	auto mouse = Sprite::createWithSpriteFrameName("menu_rata-sheet0.png");
	mouse->setPosition(size.width/2 + 20, mouse->getContentSize().height/2 - 50);
	this->addChild(mouse, 1);
	mouse->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("mouse_home")));

	auto shadow = Sprite::create("res/ingame_rata_sombra-sheet0.png");
	shadow->setPosition(mouse->getPosition().x - 10, mouse->getPosition().y + 80);
	this->addChild(shadow);
	
	auto play = MenuItemImage::create("res/btnplaymain-sheet0.png", "res/btnplaymain-sheet1.png", CC_CALLBACK_1(StartScene::menuCallback, this));
	play->setPosition(size.width / 2, size.height * 0.2);
	play->setTag(0);
	auto audioBtn = MenuItemImage::create("res/btnaudio_on.png", "res/btnaudio_on_press.png", CC_CALLBACK_1(StartScene::menuCallback, this));
	audioBtn->setPosition(size.width - audioBtn->getContentSize().width/2 - 20, size.height - audioBtn->getContentSize().height/2 - 20);
	audioBtn->setTag(1);
	auto menu = Menu::create(play, audioBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 2);

	auto hand = Sprite::create("res/menu_rata_brazo-sheet0.png");
	hand->setPosition(size.width / 2 , size.height * 0.25);
	this->addChild(hand, 2);

	

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
	auto item = static_cast<MenuItem*>(sender);
	auto tag = item->getTag();

	if (tag == 0)
		Director::getInstance()->replaceScene(TransitionFade::create(0.8f, SelectScene::createScene()));
	else if (tag == 1)
	{

	}
}