#pragma once
#include "cocos2d.h"
#include "Layers\BaseLayer.h"
#include "..\Sprites\Mouse.h"
#include "..\Sprites\Cheese.h"

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

private:
	PhysicsWorld *m_world;
	Mouse* m_mouse;
	Cheese* m_cheese;
};

