#pragma once
#include "cocos2d.h"
#include "Layers\BaseLayer.h"

USING_NS_CC;

class SplashLayer : public BaseLayer
{
public:
	SplashLayer();
	~SplashLayer();
	CREATE_FUNC(SplashLayer);
	virtual bool init() override;
	static Scene* createScene();

};

