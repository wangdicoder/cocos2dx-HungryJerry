#include "BaseLayer.h"


BaseLayer::BaseLayer()
{
}


BaseLayer::~BaseLayer()
{
}

bool BaseLayer::init()
{
	if (!Layer::init())
		return false;

	size = Director::getInstance()->getWinSize();

	return true;
}

void BaseLayer::setBackgroundImage(int index)
{
	Sprite* bg = NULL;

	switch (index)
	{
	case 0:{
			   bg = Sprite::create("res/bgmain-sheet0.png");
			   auto title = Sprite::create("res/titulo-sheet0.png");
			   title->setPosition(size.width / 2, size.height * 0.67);
			   this->addChild(title, 1);
			   break;
	}
	case 1:
		bg = Sprite::create("res/bg1-sheet.png");
		break;
	case 2:
		bg = Sprite::create("res/bg2-sheet.png");
		break;
	case 3:
		bg = Sprite::create("res/bg3-sheet.png");
		break;
	default:
		break;
	}

	bg->setPosition(size.width/2, size.height/2);
	this->addChild(bg);

	auto lampLeft = Sprite::create("res/lampara-sheet0.png");
	lampLeft->setPosition(size.width*0.15, size.height + 20);
	lampLeft->setAnchorPoint(Vec2(0.5f, 1));
	this->addChild(lampLeft, 1);
	lampLeft->runAction(RepeatForever::create(Sequence::createWithTwoActions(EaseSineInOut::create(RotateTo::create(1.3f, 10)), EaseSineInOut::create(RotateTo::create(1.3f, -10)))));

	auto lampRight = Sprite::create("res/lampara-sheet0.png");
	lampRight->setPosition(size.width*0.85, size.height + 20);
	lampRight->setAnchorPoint(Vec2(0.5f, 1));
	this->addChild(lampRight, 1);
	lampRight->runAction(RepeatForever::create(Sequence::createWithTwoActions(EaseSineInOut::create(RotateTo::create(1.3f, -10)), EaseSineInOut::create(RotateTo::create(1.3f, 10)))));
}