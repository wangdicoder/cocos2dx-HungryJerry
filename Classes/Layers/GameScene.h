#pragma once
#include "cocos2d.h"
#include "Layers\BaseLayer.h"

USING_NS_CC;

class GameScene : public BaseLayer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init() override;
	static Scene* createScene();
};

