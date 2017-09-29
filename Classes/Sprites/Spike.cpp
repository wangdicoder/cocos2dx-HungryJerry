#include "Spike.h"


Spike::Spike()
{
}


Spike::~Spike()
{
}

bool Spike::init()
{
	if (!Sprite::init())
		return false;

	initWithFile("res/ingame_spike-sheet0.png");
	setScale(0.9f);

	auto body = PhysicsBody::createBox(Size(getContentSize().width - 30, getContentSize().height /2));
	body->setDynamic(false);
	body->setContactTestBitmask(0x01);
	setPhysicsBody(body);

	setTag(7);

	return true;
}