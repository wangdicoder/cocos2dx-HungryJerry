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
	scene->getPhysicsWorld()->setGravity(Vect(0, -1500));//-900
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
	edge->setPosition(size.width / 2, size.height / 2);
	edge->setPhysicsBody(edgeBody);
	this->addChild(edge);
	edge->setTag(0);


	auto board1 = Board::create();
	board1->setPosition(size.width*0.15f, size.height *0.2);
	this->addChild(board1);
	
	m_cheese = Cheese::create();
	m_cheese->setPosition(board1->getPositionX(), board1->getPositionY() + m_cheese->getContentSize().height / 2 + board1->getContentSize().height );
	this->addChild(m_cheese, 1);

	auto board2 = Board::create();
	board2->setPosition(size.width*0.8, size.height*0.5);
	this->addChild(board2);

	m_mouse = Mouse::create();
	m_mouse->setPosition(board2->getPositionX(), board2->getPositionY() + board2->getContentSize().height / 2);
	this->addChild(m_mouse);

	auto star = Star::create();
	star->setPosition(size.width*0.3, size.height*0.3);
	this->addChild(star);


	for (int i = 0; i < 10; i++)
	{
		auto point = Sprite::create("res/ingame_circulo-sheet0.png");
		point->setPosition(-10, -10);
		point->setScale(1 - 0.05f * i);
		this->addChild(point);
		m_dotVec.pushBack(point);
	}

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	//fix physics bug
	for (int i = 0; i < 3; ++i)
		m_world->step(1 / 180.0f);


}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
	
	
	return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	for (int i = 0; i < m_dotVec.size(); i++)
	{
		m_dotVec.at(i)->setPosition(m_cheese->getPosition());
		m_dotVec.at(i)->setVisible(true);
	}

	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	Vec2 rotateVector = touch->getLocation() - m_cheese->getPosition();
	float radians = rotateVector.getAngle();
	m_applyForce = 0.2 * sqrt(pow(touch->getLocation().x - m_cheese->getPosition().x, 2) + pow(touch->getLocation().y - m_cheese->getPosition().y, 2));
	if (m_applyForce >= 140)
		m_applyForce = 140;

	for (int i = 0; i < m_dotVec.size(); i++)
	{
		auto point = m_dotVec.at(i);
		point->setPosition(m_cheese->getPositionX() + m_applyForce * cos(radians) * i, m_cheese->getPositionY() + m_applyForce * sin(radians) * i - 0.5 * 10 * i * i);
	}
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	for (int i = 0; i < m_dotVec.size(); i++)
	{
		m_dotVec.at(i)->setVisible(false);
	}

	Vec2 rotateVector = touch->getLocation() - m_cheese->getPosition();
	float radians = rotateVector.getAngle();
	m_cheese->getPhysicsBody()->applyImpulse(Vec2(cos(radians) * m_applyForce * 8000, sin(radians) * m_applyForce * 8000));
}