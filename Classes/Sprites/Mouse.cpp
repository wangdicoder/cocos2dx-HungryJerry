#include "Mouse.h"


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

bool Mouse::init()
{
	if (!Sprite::init())
		return false;

	initWithFile("res/mouse_normal.png");
	setAnchorPoint(Vec2(0.5f, 0));

	runAction(RepeatForever::create(Sequence::createWithTwoActions(ScaleTo::create(0.3f, 1, 0.95f), ScaleTo::create(0.3f, 1))));


	return true;
}