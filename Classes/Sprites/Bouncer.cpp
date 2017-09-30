#include "Bouncer.h"


Bouncer::Bouncer()
{
}


Bouncer::~Bouncer()
{
}

bool Bouncer::init()
{
	if (!Sprite::init())
		return false;

	initWithFile("res/ingame_resorte-sheet0.png");

	auto body = PhysicsBody::createBox(Size(getContentSize().width - 30, getContentSize().height / 2));
	body->setDynamic(false);
	body->getShape(0)->setRestitution(1.0f);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setDensity(1.0f);
	body->setContactTestBitmask(0x01);
	setPhysicsBody(body);

	setTag(3);

	return true;
}

