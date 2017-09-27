#include "Board.h"


Board::Board()
{
}


Board::~Board()
{
}

Board* Board::create(int index)
{
	auto ref = new Board();
	ref->init(index);
	ref->autorelease();

	return ref;
}

bool Board::init(int index)
{
	if (!Sprite::init())
		return false;

	initWithFile("res/board_short.png");

	auto body = PhysicsBody::createBox(getContentSize());
	body->setDynamic(false);
	setPhysicsBody(body);

	return true;
}

