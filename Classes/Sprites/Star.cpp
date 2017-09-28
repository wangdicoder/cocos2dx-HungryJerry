#include "Star.h"


Star::Star()
{
}


Star::~Star()
{
}

bool Star::init()
{
	if (!Sprite::init())
		return false;

	initWithFile("res/ingame_estrella-sheet0.png");

	runAction(RepeatForever::create(Sequence::createWithTwoActions(ScaleTo::create(0.2f, 0.85f, 0.85f), ScaleTo::create(0.2f, 1, 1))));
	runAction(RepeatForever::create(Sequence::createWithTwoActions(RotateTo::create(0.5f, -12), RotateTo::create(0.5f, 12))));

	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x00);
	setPhysicsBody(body);

	setTag(2);

	return true;
}

void Star::remove()
{
	auto particle = ParticleSystemQuad::create("res/stars.plist");
	particle->setPosition(getPosition());
	this->getParent()->addChild(particle);

	this->removeFromParentAndCleanup(true);
}