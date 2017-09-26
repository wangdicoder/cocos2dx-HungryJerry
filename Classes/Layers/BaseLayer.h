#pragma once
#include "cocos2d.h"

USING_NS_CC; 

class BaseLayer : public Layer
{
public:
	BaseLayer();
	~BaseLayer();
	CREATE_FUNC(BaseLayer);
	virtual bool init() override;
	void setBackgroundImage(int index);

protected:
	Size size;

};

