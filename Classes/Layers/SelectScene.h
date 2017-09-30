#pragma once
#include "cocos2d.h"
#include "Layers\BaseLayer.h"
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;

class SelectScene : public BaseLayer
{
public:
	SelectScene();
	~SelectScene();
	CREATE_FUNC(SelectScene);
	virtual bool init() override;
	static Scene* createScene();

private:
	void menuCallback(Ref* sender);
	void pageViewEvent(Ref* pSender, PageView::EventType type);
	void btnCallback(Ref *pSender, Widget::TouchEventType type);

	Vec2 tips[3];
	Sprite *m_curTip;
	PageView* pageView;
	int maxIndex;
};

