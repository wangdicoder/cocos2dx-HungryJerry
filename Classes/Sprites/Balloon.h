#pragma once
#include "cocos2d.h"

USING_NS_CC;

typedef enum BALL_TYPE
{
	RED = 0,
	YELLOW,
	BLUE
};

class Balloon: public Node
{
public:
	Balloon();
	~Balloon();
	bool init(BALL_TYPE type);
	static Balloon* create(BALL_TYPE type = RED);
	void update(float dt);
	Size getContentSize();

private:
	Size size;
	Sprite* ball;
};

