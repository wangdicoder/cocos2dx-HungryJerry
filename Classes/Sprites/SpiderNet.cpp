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
	setScale(1.9f);

	auto body = PhysicsBody::createCircle(getContentSize().width*0.7f);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x00);
	setPhysicsBody(body);

	setTag(4);

	return true;
}

