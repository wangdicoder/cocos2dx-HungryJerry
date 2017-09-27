#include "Cheese.h"


Cheese::Cheese()
{
}


Cheese::~Cheese()
{
}

bool Cheese::init()
{
	if (!Sprite::init())
		return false;

	initWithFile("res/ingame_queso-sheet0.png");
	auto normalBody = PhysicsBody::createCircle(this->getContentSize().width / 2);
	normalBody->getShape(0)->setFriction(0.3f);
	normalBody->getShape(0)->setRestitution(0.7f);
	normalBody->setLinearDamping(0.8f);
	normalBody->setAngularDamping(0.8f);
	normalBody->setCategoryBitmask(0x01);
	normalBody->setContactTestBitmask(0x01);
	normalBody->setCollisionBitmask(0x01);
	normalBody->setTag(1);
	setPhysicsBody(normalBody);

	return true;
}