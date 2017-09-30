#include "Mouse.h"


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

bool Mouse::init()
{
	if (!Sprite::init())
		return false;

	initWithSpriteFrameName("mouse_normal.png");

	/*auto earLeft = Sprite::create("res/menu_rata_oreja-sheet0.png");
	earLeft->setPosition(earLeft->getContentSize().width / 2 * 0.5f, getContentSize().height * 0.8f);
	earLeft->setScale(0.5f);
	this->addChild(earLeft);

	auto earRight = Sprite::create("res/menu_rata_oreja-sheet0.png");
	earLeft->setPosition(getContentSize().width - earRight->getContentSize().width / 2 * 0.5f, getContentSize().height * 0.8f);
	earRight->setScale(earLeft->getScale());
	earRight->setFlippedX(true);
	this->addChild(earRight);*/

	chair = Sprite::create("res/sprite2-sheet0.png");
	chair->setPosition(getContentSize().width/2, getContentSize().height/2 + 22);
	addChild(chair);
	chair->setVisible(false);

	//runAction(RepeatForever::create(Sequence::createWithTwoActions(ScaleTo::create(0.3f, 1, 0.95f), ScaleTo::create(0.3f, 1))));

	auto body = PhysicsBody::createCircle(getContentSize().width/2 - 30);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setContactTestBitmask(0x01);
	setPhysicsBody(body);

	setTag(0);
	isDisplayBalloon = false;
	return true;
}

void Mouse::playEatingAnimation()
{
	this->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("eatingAnimation1")));
}

void Mouse::setIsDisplayBalloon(bool flag)
{
	isDisplayBalloon = flag;
	chair->setVisible(flag);
}