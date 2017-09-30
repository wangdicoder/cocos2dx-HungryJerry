#pragma once
#include "cocos2d.h"
#include "Layers\BaseLayer.h"
#include "..\Sprites\Mouse.h"
#include "..\Sprites\Cheese.h"
#include "..\Sprites\SpiderNet.h"
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;
USING_NS_CC;

class GameScene : public BaseLayer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init() override;
	static Scene* createScene();
	void setPhyWorld(PhysicsWorld *world) { m_world = world; };
	void update(float dt);
	bool onContactBegin(PhysicsContact& contact);
	void onContactSeperate(PhysicsContact& contact);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void initUI();

private:
	PhysicsWorld *m_world;
	Mouse* m_mouse;
	Vector<Sprite*> m_dotVec;
	float m_applyForce;
	SpiderNet* netWithCheese;
	void btnCallback(Ref *pSender);
	Vector<Cheese*> cheeseVec;
	Cheese* touchCheese;

};

