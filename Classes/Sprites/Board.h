#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Board: public Sprite
{
public:
	Board();
	~Board();
	bool init(int index);
	static Board* create(int index = 0);
};

