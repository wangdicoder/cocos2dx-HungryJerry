#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Laser: public Node
{
public:
	Laser();
	~Laser();
	bool init(int index);
	static Laser* create(int index = 0);
};

