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

	runAction(RepeatForever::create(Sequence::createWithTwoActions(ScaleTo::create(0.2f, 0.85f), ScaleTo::create(0.2f, 1))));
	runAction(RepeatForever::create(Sequence::createWithTwoActions(RotateTo::create(0.5f, -12), RotateTo::create(0.5f, 12))));


	return true;
}