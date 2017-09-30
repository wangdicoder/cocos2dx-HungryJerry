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

	if (index == 0)
		initWithFile("res/board_short.png");
	else
		initWithFile("res/board_long.png");

	auto body = PhysicsBody::createBox(getContentSize());
	body->setDynamic(false);
	setPhysicsBody(body);

	return true;
}

