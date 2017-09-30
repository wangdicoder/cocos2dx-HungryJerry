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

	//runAction(RepeatForever::create(Sequence::createWithTwoActions(ScaleTo::create(0.3f, 1, 0.95f), ScaleTo::create(0.3f, 1))));

	auto body = PhysicsBody::createCircle(getContentSize().width/2 - 30);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setContactTestBitmask(0x01);
	setPhysicsBody(body);

	setTag(0);

	return true;
}

void Mouse::playEatingAnimation()
{
	this->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("eatingAnimation1")));
}