#include "Laser.h"


Laser::Laser()
{
}


Laser::~Laser()
{
}

Laser* Laser::create(int index, bool blink)
{
	auto ref = new Laser();
	ref->init(index, blink);
	ref->autorelease();

	return ref;
}

bool Laser::init(int index, bool blink)
{
	if (!Node::init())
		return false;

	
	auto laser = Sprite::createWithSpriteFrameName("laser0.png");
	laser->setTag(5);
	addChild(laser);
	laser->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("laser")));
	auto laserBody = PhysicsBody::createBox(laser->getContentSize());
	laserBody->setContactTestBitmask(0x01);
	laserBody->setDynamic(false);
	laser->setPhysicsBody(laserBody);

	auto laserLeft = Sprite::create("res/laser_left.png");
	laserLeft->setPositionX(laser->getPositionX() - laser->getContentSize().width/2 - laserLeft->getContentSize().width/2);
	this->addChild(laserLeft);
	auto leftCover = Sprite::create("res/rayo_covertor_d-sheet0.png");
	leftCover->setPosition(laserLeft->getPositionX() + laserLeft->getContentSize().width/2 - leftCover->getContentSize().width + 8, laserLeft->getPositionY()+2);
	this->addChild(leftCover);
	leftCover->setAnchorPoint(Vec2(0, 0.5f));
	leftCover->setFlipX(true);
	leftCover->runAction(RepeatForever::create(Sequence::createWithTwoActions(EaseSineIn::create(ScaleTo::create(0.1f, 1.1f, 1.1f)), EaseSineIn::create(ScaleTo::create(0.15f, 1, 1)))));

	auto laserRight = Sprite::create("res/laser_right.png");
	laserRight->setPositionX(laser->getPositionX() + laser->getContentSize().width / 2 + laserRight->getContentSize().width / 2);
	this->addChild(laserRight);
	auto rightCover = Sprite::create("res/rayo_covertor_d-sheet0.png");
	rightCover->setPosition(laserRight->getPositionX() - laserRight->getContentSize().width / 2 + rightCover->getContentSize().width - 8, laserRight->getPositionY()+2);
	rightCover->setAnchorPoint(Vec2(1, 0.5f));
	this->addChild(rightCover);
	rightCover->runAction(RepeatForever::create(Sequence::createWithTwoActions(EaseSineIn::create(ScaleTo::create(0.1f, 1.1f, 1.1f)), EaseSineIn::create(ScaleTo::create(0.15f, 1, 1)))));

	float scale = 0.57f;
	if (index == 1)
	{
		laser->setScaleX(scale);
		laserLeft->setPositionX(laser->getPositionX() - laser->getContentSize().width / 2 * scale - laserLeft->getContentSize().width / 2);
		laserRight->setPositionX(laser->getPositionX() + laser->getContentSize().width / 2 * scale + laserRight->getContentSize().width / 2);
		leftCover->setPositionX(laserLeft->getPositionX() + laserLeft->getContentSize().width / 2 - leftCover->getContentSize().width + 8);
		rightCover->setPositionX(laserRight->getPositionX() - laserRight->getContentSize().width / 2 + rightCover->getContentSize().width - 8);

		//laser->runAction(Place::create(Vec2(3000, 3000)));
	}

	auto bodyLeft = PhysicsBody::createBox(laserLeft->getContentSize());
	bodyLeft->setDynamic(false);
	laserLeft->setPhysicsBody(bodyLeft);
	auto bodyRight = PhysicsBody::createBox(laserRight->getContentSize());
	bodyRight->setDynamic(false);
	laserRight->setPhysicsBody(bodyRight);

	if (blink)
	{
		float delayTime = 1.2f;
		laser->runAction(RepeatForever::create(Sequence::create(DelayTime::create(delayTime), Place::create(Vec2(3000, 3000)), DelayTime::create(delayTime), Place::create(Vec2(0, 0)), NULL)));
	}
	
	return true;
}

