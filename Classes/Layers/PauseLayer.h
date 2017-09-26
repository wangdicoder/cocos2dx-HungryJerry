#pragma once
#include "cocos2d.h"
#include "Layers\BaseLayer.h"

USING_NS_CC;

class PauseLayer : public BaseLayer
{
public:
	PauseLayer();
	~PauseLayer();
	CREATE_FUNC(PauseLayer);
	virtual bool init() override;
	static Scene* createScene();

private:
	void menuCallback(Ref* sender);

};

