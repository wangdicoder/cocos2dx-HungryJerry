#pragma once
#include "BaseLayer.h"

class IntroLayer : public BaseLayer
{
public:
	IntroLayer();
	~IntroLayer();
	CREATE_FUNC(IntroLayer);
	virtual bool init() override;

};

