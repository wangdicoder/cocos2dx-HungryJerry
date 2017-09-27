#include "GameScene.h"
#include "StartScene.h"
#include "GameManager.h"
#include "GameoverLayer.h"
#include "..\Sprites\Board.h"
#include "..\Sprites\Star.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, -900));//-900
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setAutoStep(false);
	auto layer = GameScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!BaseLayer::init())
		return false;

	setBackgroundImage(1);

	auto edge = Node::create();
	auto edgeBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->getShape(0)->setRestitution(1.0f);
	edgeBody->getShape(0)->setFriction(0);
	edgeBody->getShape(0)->setDensity(1.0f);
	edge->setPosition(size.width / 2, size.height / 2);
	edge->setPhysicsBody(edgeBody);
	this->addChild(edge);
	edge->setTag(0);


	auto board1 = Board::create();
	board1->setPosition(size.width*0.15f, size.height *0.2);
	this->addChild(board1);
	
	m_cheese = Cheese::create();
	m_cheese->setPosition(board1->getPositionX(), board1->getPositionY() + m_cheese->getContentSize().height / 2 + board1->getContentSize().height / 2);
	this->addChild(m_cheese);

	auto board2 = Board::create();
	board2->setPosition(size.width*0.8, size.height*0.5);
	this->addChild(board2);

	m_mouse = Mouse::create();
	m_mouse->setPosition(board2->getPositionX(), board2->getPositionY() + board2->getContentSize().height / 2);
	this->addChild(m_mouse);

	auto star = Star::create();
	star->setPosition(size.width*0.3, size.height*0.3);
	this->addChild(star);

	scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	//fix physics bug
	for (int i = 0; i < 3; ++i)
		m_world->step(1 / 180.0f);


}