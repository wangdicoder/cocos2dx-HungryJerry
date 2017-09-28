#include "SpiderNet.h"


SpiderNet::SpiderNet()
{
}


SpiderNet::~SpiderNet()
{
}

bool SpiderNet::init()
{
	if (!Sprite::init())
		return false;

	initWithFile("res/ingame_telarania-sheet0.png");

	auto body = PhysicsBody::createCircle(getContentSize().width*0.25f);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x00);
	body->setTag(2);
	setPhysicsBody(body);

	setTag(4);

	return true;
}

void SpiderNet::playEffect()
{
	runAction(Sequence::createWithTwoActions(EaseSineIn::create(ScaleTo::create(0.2f, 1.07f, 1.07f)), EaseSineIn::create(ScaleTo::create(0.2f, 1, 1))));
}

void SpiderNet::addPhysicsBody()
{
	auto body = PhysicsBody::createCircle(getContentSize().width*0.25f);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x00);
	body->setTag(2);
	setPhysicsBody(body);
}