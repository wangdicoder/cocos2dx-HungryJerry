#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Cheese : public Sprite
{
public:
	Cheese();
	~Cheese();
	bool init();
	CREATE_FUNC(Cheese);
	void addPhysicsBody();
	void removePhysicsBody(PhysicsWorld *world);
	CC_SYNTHESIZE(bool, isHasPhysBody, IsHasPhysBody);
};

