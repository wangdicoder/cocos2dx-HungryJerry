#include "GameOverLayer.h"
#include "StartScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define BTN "res/btnclick.ogg"
#define STARMOVE "res/starMove.mp3"
#define CIRCLE "res/estrellasale.ogg"
#define BMG "res/ganarmusica.ogg"

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

	int starNum = GameManager::getInstance()->getStarNum();

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
	createStar(starRate->getPosition(), starNum);

	auto scoreBg = Sprite::create("res/bgscorecomplete-sheet0.png");
	scoreBg->setPosition(size.width/2, scoreBg->getContentSize().height /2 + 25);
	this->addChild(scoreBg);

	auto label = Label::createWithBMFont("res/myfont.fnt", "Score");
	label->setPosition(scoreBg->getContentSize().width/2, scoreBg->getContentSize().height * 0.73);
	label->setScale(1.5f);
	scoreBg->addChild(label);

	auto scoreLabel = Label::createWithBMFont("res/myfont.fnt", "18320");
	scoreLabel->setPosition(scoreBg->getContentSize().width / 2, scoreBg->getContentSize().height * 0.3);
	scoreLabel->setScale(2.5f);
	scoreBg->addChild(scoreLabel);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [](Touch *touch, Event *event){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	if (GameManager::getInstance()->getLevelNum() >= GameManager::getInstance()->readGameIndexFromFile() && GameManager::getInstance()->getLevelNum() < 21)
		GameManager::getInstance()->writeGameIndexToFile();

	SimpleAudioEngine::getInstance()->playBackgroundMusic(BMG);

	return true;
}

void GameOverLayer::menuCallback(Ref* sender)
{
	auto item = static_cast<MenuItemFont*>(sender);
	int nTag = item->getTag();

	if (nTag == 0)
	{
		if (GameManager::getInstance()->getLevelNum() == 27)
		{
			Director::getInstance()->replaceScene(TransitionFade::create(0.8f, SelectScene::createScene()));
		}
		else
		{
			GameManager::getInstance()->setLevelNum(GameManager::getInstance()->getLevelNum() + 1);
			Director::getInstance()->replaceScene(TransitionFade::create(0.8f, GameScene::createScene()));
		}
	}
	else if (nTag == 1)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.8f, SelectScene::createScene()));
	}
	else if (nTag == 2)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.8f, GameScene::createScene()));
	}

	SimpleAudioEngine::getInstance()->playEffect(BTN);
}

void GameOverLayer::createStar(Vec2 panelPos, int num)
{
	int starNum = GameManager::getInstance()->getStarNum();
	if (starNum < 1)
		return;
	{
		auto star = Sprite::create("res/starscomplete-sheet0.png");
		star->setPosition(size.width*0.25, -star->getContentSize().height / 2);
		addChild(star, 1);
		star->setRotation(90);
		auto move1 = MoveTo::create(0.4f, Vec2(size.width / 2, size.height / 2));
		auto move2 = MoveTo::create(0.1f, Vec2(size.width / 2 - star->getContentSize().width - 18, size.height / 2 - 60));
		auto scale1 = ScaleTo::create(0.4f, 3.0f);
		auto scale2 = ScaleTo::create(0.1f, 1);
		auto rotate = RotateTo::create(0.5f, 0);
		auto spawn1 = EaseBackOut::create(Spawn::create(move1, scale1, NULL));
		auto spawn2 = Spawn::create(move2, scale2, NULL);
		star->runAction(Sequence::create(DelayTime::create(0.5f), spawn1, spawn2, CallFuncN::create([=](Node* sender){ createCircle(sender->getPosition()); }), NULL));
		star->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){SimpleAudioEngine::getInstance()->playEffect(STARMOVE); }), rotate, NULL));


	}

	if (starNum < 2)
		return;
	{
		auto star = Sprite::create("res/starscomplete-sheet0.png");
		star->setPosition(size.width*0.5, -star->getContentSize().height / 2);
		addChild(star, 1);
		star->setRotation(90);
		auto move1 = MoveTo::create(0.4f, Vec2(size.width / 2, size.height / 2));
		auto move2 = MoveTo::create(0.1f, Vec2(size.width / 2 - 3, size.height / 2 - 38));
		auto scale1 = ScaleTo::create(0.4f, 3.0f);
		auto scale2 = ScaleTo::create(0.1f, 1);
		auto rotate = RotateTo::create(0.5f, 0);
		auto spawn1 = EaseBackOut::create(Spawn::create(move1, scale1, NULL));
		auto spawn2 = Spawn::create(move2, scale2, NULL);
		star->runAction(Sequence::create(DelayTime::create(1.0f), spawn1, spawn2, CallFuncN::create([=](Node* sender){ createCircle(sender->getPosition()); }), NULL));
		star->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=](){SimpleAudioEngine::getInstance()->playEffect(STARMOVE); }), rotate, NULL));

	}

	if (starNum < 3)
		return;
	{
		auto star = Sprite::create("res/starscomplete-sheet0.png");
		star->setPosition(size.width*0.75, -star->getContentSize().height / 2);
		addChild(star, 1);
		star->setRotation(-90);
		auto move1 = MoveTo::create(0.4f, Vec2(size.width / 2, size.height / 2));
		auto move2 = MoveTo::create(0.1f, Vec2(size.width / 2 + star->getContentSize().width + 10, size.height / 2 -60));
		auto scale1 = ScaleTo::create(0.4f, 3.0f);
		auto scale2 = ScaleTo::create(0.1f, 1);
		auto rotate = RotateTo::create(0.5f, 0);
		auto spawn1 = EaseBackOut::create(Spawn::create(move1, scale1, NULL));
		auto spawn2 = Spawn::create(move2, scale2, NULL);
		star->runAction(Sequence::create(DelayTime::create(1.5f), spawn1, spawn2, CallFuncN::create([=](Node* sender){ createCircle(sender->getPosition()); }), NULL));
		star->runAction(Sequence::create(DelayTime::create(1.5f), CallFunc::create([=](){SimpleAudioEngine::getInstance()->playEffect(STARMOVE); }), rotate, NULL));

	}


}

void GameOverLayer::createCircle(Vec2 pos)
{
	auto circle = Sprite::create("res/emiter_estrella-sheet0.png");
	circle->setPosition(pos);
	addChild(circle);
	circle->setScale(0);
	circle->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.6f, 1.7f)), FadeOut::create(0.4f), NULL));

	auto particle = ParticleSystemQuad::create("res/star.plist");
	particle->setPosition(pos);
	addChild(particle);

	SimpleAudioEngine::getInstance()->playEffect(CIRCLE);
}