#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Bouncer: public Sprite
{
public:
	Bouncer();
	~Bouncer();
	bool init();
	CREATE_FUNC(Bouncer);
};

