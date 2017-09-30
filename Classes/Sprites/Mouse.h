#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Mouse: public Sprite
{
public:
	Mouse();
	~Mouse();
	bool init();
	CREATE_FUNC(Mouse);
	void playEatingAnimation();
	//CC_SYNTHESIZE(bool, isDisplayBalloon, IsDisplayBalloon);
	void setIsDisplayBalloon(bool flag);
	bool getIsDisplayBalloon(){ return isDisplayBalloon; }

private:
	Sprite* chair;
	bool isDisplayBalloon;
};

