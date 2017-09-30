#include "SelectScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "StartScene.h"

SelectScene::SelectScene()
{
}


SelectScene::~SelectScene()
{
}

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();
	scene->addChild(layer);

	return scene;
}

bool SelectScene::init()
{
	if (!BaseLayer::init())
		return false;

	setBackgroundImage(1);

	auto pignBg = Sprite::create("res/selector_bg_pagina-sheet0.png");
	pignBg->setPosition(size.width/2, size.height*0.1);
	this->addChild(pignBg);

	//add tips
	for (int i = 0; i < 3; i++)
	{
		auto tip = Sprite::create("res/select.png");
		tip->setPosition(Vec2(size.width / 2 - (tip->getContentSize().width / 2 + 10) * 1 + (tip->getContentSize().width + 10) * 1 * i, tip->getContentSize().height));
		this->addChild(tip);
		tips[i] = Vec2(tip->getPosition());
		if (i == 1)
			pignBg->setPosition(tip->getPosition());
	}

	m_curTip = Sprite::create("res/select_in.png");
	m_curTip->setPosition(tips[0]);
	addChild(m_curTip);

	maxIndex = 5;
	int index = 0;
	int gapWidth = 80;
	Button *btn = NULL;

	pageView = PageView::create();
	pageView->setContentSize(Size(size.width, size.height));
	pageView->setPosition(Vec2::ZERO);
	pageView->addEventListener(CC_CALLBACK_2(SelectScene::pageViewEvent, this));

	//page 1
	Layout* layout = Layout::create();
	layout->setContentSize(Size(size.width, size.height));

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 5; j++){
			index++;
			if (index <= maxIndex)
				btn = Button::create("res/btnnivel-sheet0.png");
			else
				btn = Button::create("res/btnnivel-sheet2.png");
			static int startX = (size.width - btn->getContentSize().width * 5 - gapWidth * 4) / 2 + btn->getContentSize().width / 2;
			static int startY = size.height - (size.height - btn->getContentSize().height * 2) / 2 - btn->getContentSize().height/2;
			btn->setPosition(Vec2(startX + btn->getContentSize().width * j + gapWidth*j, startY - btn->getContentSize().height * i - gapWidth*i));
			btn->setTag(index);
			btn->addTouchEventListener(CC_CALLBACK_2(SelectScene::btnCallback, this));
			layout->addChild(btn);

			if (index <= maxIndex)
			{
				auto label = Label::createWithBMFont("res/myfont.fnt", Value(index).asString());
				label->setScale(2.0f);
				label->setPosition(btn->getContentSize().width / 2, btn->getContentSize().height / 2 + 2);
				btn->addChild(label);
			}
		}
	}

	pageView->addPage(layout);

	//page 2
	layout = Layout::create();
	layout->setContentSize(Size(size.width, size.height));

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 5; j++){
			index++;
			if (index <= maxIndex)
				btn = Button::create("res/btnnivel-sheet0.png");
			else
				btn = Button::create("res/btnnivel-sheet2.png");
			static int startX = (size.width - btn->getContentSize().width * 5 - gapWidth * 4) / 2 + btn->getContentSize().width / 2;
			static int startY = size.height - (size.height - btn->getContentSize().height * 2) / 2 - btn->getContentSize().height / 2;
			btn->setPosition(Vec2(startX + btn->getContentSize().width * j + gapWidth*j, startY - btn->getContentSize().height * i - gapWidth*i));
			btn->setTag(index);
			btn->addTouchEventListener(CC_CALLBACK_2(SelectScene::btnCallback, this));
			layout->addChild(btn);

			if (index <= maxIndex)
			{
				auto label = Label::createWithBMFont("res/myfont.fnt", Value(index).asString());
				label->setScale(2.0f);
				label->setPosition(btn->getContentSize().width / 2, btn->getContentSize().height / 2 + 2);
				btn->addChild(label);
			}
		}
	}
	pageView->addPage(layout);

	//page 3
	layout = Layout::create();
	layout->setContentSize(Size(size.width, size.height));

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 5; j++){
			index++;
			if (index <= maxIndex)
				btn = Button::create("res/btnnivel-sheet0.png");
			else
				btn = Button::create("res/btnnivel-sheet2.png");
			static int startX = (size.width - btn->getContentSize().width * 5 - gapWidth * 4) / 2 + btn->getContentSize().width / 2;
			static int startY = size.height - (size.height - btn->getContentSize().height * 2) / 2 - btn->getContentSize().height / 2;
			btn->setPosition(Vec2(startX + btn->getContentSize().width * j + gapWidth*j, startY - btn->getContentSize().height * i - gapWidth*i));
			btn->setTag(index);
			btn->addTouchEventListener(CC_CALLBACK_2(SelectScene::btnCallback, this));
			layout->addChild(btn);

			if (index <= maxIndex)
			{
				auto label = Label::createWithBMFont("res/myfont.fnt", Value(index).asString());
				label->setScale(2.0f);
				label->setPosition(btn->getContentSize().width / 2, btn->getContentSize().height / 2 + 2);
				btn->addChild(label);
			}
		}
	}

	pageView->addPage(layout);
	addChild(pageView);

	auto menuBtn = MenuItemImage::create("res/btnmenusel-sheet0.png", "res/btnmenusel-sheet1.png", CC_CALLBACK_1(SelectScene::menuCallback, this));
	menuBtn->setPosition(menuBtn->getContentSize().width/2 + 20, size.height - menuBtn->getContentSize().height / 2 - 20);
	auto menu = Menu::create(menuBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 10);

	auto scoreContainer = Sprite::create("res/starsel-sheet0.png");
	scoreContainer->setPosition(size.width/2, size.height - scoreContainer->getContentSize().height / 2 - 40);
	this->addChild(scoreContainer);

	int currStarNum = 20;
	char str[50] = { 0 };
	sprintf(str, "%d", currStarNum);
	auto starLabel = Label::createWithBMFont("res/myfont.fnt", str);
	starLabel->setAnchorPoint(Vec2(0, 0.5f));
	starLabel->setScale(1.5f);
	starLabel->setPosition(Vec2(scoreContainer->getContentSize().width * 0.15f, scoreContainer->getContentSize().height/2));
	scoreContainer->addChild(starLabel);

	auto totalStarLabel = Label::createWithBMFont("res/myfont.fnt", "90");
	totalStarLabel->setAnchorPoint(Vec2(0, 0.5f));
	totalStarLabel->setScale(1.5f);
	totalStarLabel->setPosition(Vec2(scoreContainer->getContentSize().width * 0.3f, scoreContainer->getContentSize().height / 2));
	scoreContainer->addChild(totalStarLabel);

	sprintf(str, "SCORE: %d", currStarNum * 250);
	auto scoreLabel = Label::createWithBMFont("res/myfont.fnt", str);
	scoreLabel->setAnchorPoint(Vec2(1, 0.5f));
	scoreLabel->setScale(1.5f);
	scoreLabel->setPosition(Vec2(scoreContainer->getContentSize().width - 10, scoreContainer->getContentSize().height / 2));
	scoreContainer->addChild(scoreLabel);

	return true;
}

void SelectScene::menuCallback(Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.8f, StartScene::createScene()));
	
}

void SelectScene::pageViewEvent(Ref* pSender, PageView::EventType type)
{
	PageView* pageView = dynamic_cast<PageView*>(pSender);
	int n = pageView->getCurPageIndex();

	m_curTip->setPosition(tips[n]);

}

void SelectScene::btnCallback(Ref *pSender, Widget::TouchEventType type)
{
	auto btn = static_cast<Button*>(pSender);
	int tag = btn->getTag();

	if (type == Widget::TouchEventType::ENDED)
	{
		if (tag <= maxIndex)
		{
			//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			GameManager::getInstance()->setLevelNum(tag);
			Director::getInstance()->replaceScene(TransitionFade::create(0.8f, GameScene::createScene()));
		}
		//SimpleAudioEngine::getInstance()->playEffect(BTN);
	}
}