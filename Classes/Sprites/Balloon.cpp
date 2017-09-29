#include "Balloon.h"


Balloon::Balloon()
{
}


Balloon::~Balloon()
{
}

Balloon* Balloon::create(BALL_TYPE type)
{
	auto ref = new Balloon();
	ref->init(type);
	ref->autorelease();

	return ref;
}

bool Balloon::init(BALL_TYPE type)
{
	if (!Node::init())
		return false;

	size = Director::getInstance()->getWinSize();

	Sprite* ball = NULL;
	switch (type)
	{
	case RED:
		ball = Sprite::create("res/red_balloon.png");
		break;
	case YELLOW:
		ball = Sprite::create("res/yellow_balloon.png");
		break;
	case BLUE:
		ball = Sprite::create("res/sprite-sheet1.png");
		break;
	default:
		break;
	}
	ball->setTag(6);
	this->addChild(ball);
	
	auto rope = Sprite::create("res/balloon_rope.png");
	rope->setAnchorPoint(Vec2(0.5, 1));
	rope->setPosition(ball->getContentSize().width/2, 0);
	ball->addChild(rope);

	auto body = PhysicsBody::createCircle(ball->getContentSize().width/2);
	body->setDynamic(false);
	ball->setPhysicsBody(body);

	scheduleUpdate();

	return true;
}

void Balloon::update(float dt)
{
	runAction(Place::create(Vec2(getPositionX(), getPositionY() + 15)));
	if (getPositionY() - getContentSize().height >= size.height){
		runAction(Place::create(Vec2(getPositionX(), -getContentSize().height/2)));
	}
}

Size Balloon::getContentSize()
{
	return Size(100, 235);
}

