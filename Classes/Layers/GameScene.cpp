#include "GameScene.h"
#include "StartScene.h"
#include "GameManager.h"
#include "GameOverLayer.h"
#include "..\Sprites\Board.h"
#include "..\Sprites\Star.h"
#include "..\Sprites\Bouncer.h"
#include "..\Sprites\Laser.h"
#include "..\Sprites\Balloon.h"
#include "..\Sprites\Spike.h"

#define FORCE_SCALE 6200

GameScene::GameScene()
{
	touchCheese = nullptr;
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

	GameManager::getInstance()->createAnimation();
	setBackgroundImage(1);

	auto edge = Node::create();
	auto edgeBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edge->setPosition(size.width / 2, size.height / 2);
	edge->setPhysicsBody(edgeBody);
	this->addChild(edge);
	edge->setTag(0);

	initUI();

	//read tiledMap info and render objects
	char str[30] = { 0 };
	sprintf(str, "levels/level%d.tmx", 6);

	auto map = TMXTiledMap::create(str);
	map->setAnchorPoint(Vec2(0.5f, 0.5f));
	map->setPosition(size.width / 2, size.height / 2);
	addChild(map);

	float offsetY = -(map->getContentSize().height - size.height) / 2 + map->getTileSize().height / 2;
	float offsetX = -(map->getContentSize().width - size.width) / 2 + map->getTileSize().width / 2;

	auto objLayer = map->getObjectGroup("obj");
	auto objInfo = objLayer->getObjects();

	for (int i = 0; i < objInfo.size(); i++)
	{
		auto item = objInfo.at(i).asValueMap();

		if (item["type"].asString() == "cheese")
		{
			auto board = Board::create();
			board->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			this->addChild(board);

			auto cheese = Cheese::create();
			cheese->setPosition(board->getPositionX(), board->getPositionY() + cheese->getContentSize().height / 2 + board->getContentSize().height / 2);
			this->addChild(cheese, 1);
			cheeseVec.pushBack(cheese);
		}
		else if (item["type"].asString() == "star")
		{
			auto star = Star::create();
			star->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			this->addChild(star);
		}
		else if (item["type"].asString() == "mouse")
		{
			auto board = Board::create();
			board->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			this->addChild(board);

			m_mouse = Mouse::create();
			m_mouse->setPosition(board->getPositionX(), board->getPositionY() + m_mouse->getContentSize().height / 2 + board->getContentSize().height / 2);
			this->addChild(m_mouse);
		}
		else if (item["type"].asString() == "board")
		{
			auto board = Board::create(item["size"].asInt());
			board->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			this->addChild(board);
		}
		else if (item["type"].asString() == "bouncer")
		{
			auto bouncer = Bouncer::create();
			bouncer->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			bouncer->runAction(RotateTo::create(0, item["rotate"].asFloat()));
			this->addChild(bouncer);
		}
		else if (item["type"].asString() == "net")
		{
			auto net = SpiderNet::create();
			net->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			this->addChild(net);
		}
		else if (item["type"].asString() == "laser")
		{
			bool blink = item["blink"].asBool();
			Laser* laser = NULL;

			if (item["size"].asInt() == 0)
				laser = Laser::create(0, blink);
			else if (item["size"].asInt() == 1)
				laser = Laser::create(1, blink);
			
			laser->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			if (item["ver"].asBool())
				laser->setRotation(90);

			this->addChild(laser);
		}
		else if (item["type"].asString() == "balloon")
		{
			Balloon* balloon = NULL;
			if (item["color"].asString() == "red")
				balloon = Balloon::create(RED);
			else if (item["color"].asString() == "yellow")
				balloon = Balloon::create(YELLOW);
			else if (item["color"].asString() == "blue")
				balloon = Balloon::create(BLUE);

			balloon->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			this->addChild(balloon);
		}
		else if (item["type"].asString() == "spike")
		{
			auto spike = Spike::create();
			spike->setPosition(item["x"].asFloat() + offsetX, item["y"].asFloat() + offsetY);
			this->addChild(spike);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		auto point = Sprite::create("res/ingame_circulo-sheet0.png");
		point->setPosition(-10, -10);
		point->setScale(1 - 0.05f * i);
		this->addChild(point);
		m_dotVec.pushBack(point);
	}

	auto gameOverLayer = GameOverLayer::create();
	//this->addChild(gameOverLayer, 5);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	//contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

void GameScene::initUI()
{
	auto replayBtn = MenuItemImage::create("res/btnreset-sheet0.png", "res/btnreset-sheet1.png", CC_CALLBACK_1(GameScene::btnCallback, this));
	replayBtn->setPosition(size.width - replayBtn->getContentSize().width/2 - 5, size.height - replayBtn->getContentSize().height/2 - 5);
	replayBtn->setTag(0);
	auto menu = Menu::create(replayBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

}

void GameScene::update(float dt)
{
	//fix physics bug
	for (int i = 0; i < 3; ++i)
		m_world->step(1 / 180.0f);

	if (cheeseVec.size() <= 0)
	{
		unscheduleUpdate();
		scheduleOnce([&](float dt){
			this->addChild(GameOverLayer::create(), 10);
		}, 0.8f, "success");
	}
}

/**
	tag
	0: mouse
	1: cheese
	2: star
	3: bouncer
	4: spiderNet
	5: laser
	6: balloon
	7: thorn
	**/

bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (m_mouse != nullptr)
	{
		if (nodeA->getTag() == 0 || nodeB->getTag() == 0)
		{
			m_mouse->playEatingAnimation();
			Cheese* cheese = NULL;
			if (nodeA->getTag() == 1)
				cheese = static_cast<Cheese*>(nodeA);
			else if (nodeB->getTag() == 1)
				cheese = static_cast<Cheese*>(nodeB);
			cheeseVec.eraseObject(cheese);
			cheese->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 2)
		{
			auto star = (Star*)nodeA;
			star->remove();
		}
		else if (nodeB->getTag() == 2)
		{
			auto star = (Star*)nodeB;
			star->remove();
		}
		else if (nodeA->getTag() == 3 )
		{
			auto bouncer = (Bouncer*)nodeA;
			float radians = CC_DEGREES_TO_RADIANS(bouncer->getRotation() - 90);
			//m_cheese->getPhysicsBody()->applyImpulse(Vec2(cos(radians) * m_applyForce * FORCE_SCALE * 2, sin(radians) * m_applyForce * FORCE_SCALE * 2));
		}
		else if (nodeB->getTag() == 3)
		{
			auto bouncer = (Bouncer*)nodeB;
			float radians = CC_DEGREES_TO_RADIANS(bouncer->getRotation() - 90);
			//m_cheese->getPhysicsBody()->applyImpulse(Vec2(cos(radians) * m_applyForce * FORCE_SCALE * 2, sin(radians) * m_applyForce * FORCE_SCALE * 2));
		}
		else if (nodeA->getTag() == 4)
		{
			auto net = (SpiderNet*)nodeA;
			net->playEffect();
			net->getPhysicsBody()->setContactTestBitmask(0x00);
			netWithCheese = net;

			Cheese* cheese = (Cheese*)nodeB;
			cheese->removePhysicsBody();
		}
		else if (nodeB->getTag() == 4)
		{
			auto net = (SpiderNet*)nodeB;
			net->playEffect();
			net->getPhysicsBody()->setContactTestBitmask(0x00);
			netWithCheese = net;

			Cheese* cheese = (Cheese*)nodeA;
			cheese->removePhysicsBody();
		}
		else if (nodeA->getTag() == 5 || nodeB->getTag() == 5 || nodeA->getTag() == 7 || nodeB->getTag() == 7)
		{
			Cheese* cheese = NULL;
			if (nodeA->getTag() == 1)
				cheese = static_cast<Cheese*>(nodeA);
			else if (nodeB->getTag() == 1)
				cheese = static_cast<Cheese*>(nodeB);
			cheese->removeFromParentAndCleanup(true);

			scheduleOnce([&](float dt){
				Director::getInstance()->replaceScene(TransitionFade::create(0.8f, GameScene::createScene()));
			}, 1.0f, "replay");
		}
	}


	return true;
}

void GameScene::onContactSeperate(PhysicsContact& contact)
{

}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	if (cheeseVec.size() > 0)
	{
		for (int i = 0; i < cheeseVec.size(); i++)
		{
			if (cheeseVec.at(i)->getBoundingBox().containsPoint(touch->getLocation()))
			{
				touchCheese = cheeseVec.at(i);
			}
		}

		if (touchCheese != nullptr)
		{
			for (int i = 0; i < m_dotVec.size(); i++)
			{
				m_dotVec.at(i)->setPosition(touchCheese->getPosition());
				m_dotVec.at(i)->setVisible(true);
			}
		}
	}

	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	if (touchCheese != nullptr)
	{
		Vec2 rotateVector = touch->getLocation() - touchCheese->getPosition();
		float radians = rotateVector.getAngle();
		m_applyForce = 0.2 * sqrt(pow(touch->getLocation().x - touchCheese->getPosition().x, 2) + pow(touch->getLocation().y - touchCheese->getPosition().y, 2));
		if (m_applyForce >= 140)
			m_applyForce = 140;

		for (int i = 0; i < m_dotVec.size(); i++)
		{
			auto point = m_dotVec.at(i);
			point->setPosition(touchCheese->getPositionX() + m_applyForce * cos(radians) * i, touchCheese->getPositionY() + m_applyForce * sin(radians) * i - 0.5 * 10 * i * i);
		}
	}
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	if (touchCheese != nullptr && !touchCheese->getIsHasPhysBody())
	{
		touchCheese->addPhysicsBody();
		scheduleOnce([&](float dt){
			this->netWithCheese->getPhysicsBody()->setContactTestBitmask(0x01);
		}, 0.4f, "addNetBody");
	}

	if (touchCheese != nullptr)
	{
		for (int i = 0; i < m_dotVec.size(); i++)
		{
			m_dotVec.at(i)->setVisible(false);
		}

		Vec2 rotateVector = touch->getLocation() - touchCheese->getPosition();
		float radians = rotateVector.getAngle();
		touchCheese->getPhysicsBody()->applyImpulse(Vec2(cos(radians) * m_applyForce * FORCE_SCALE, sin(radians) * m_applyForce * FORCE_SCALE));
	}

	touchCheese = nullptr;
}

void GameScene::btnCallback(Ref *pSender)
{
	auto menuItem = static_cast<MenuItem*>(pSender);
	int tag = menuItem->getTag();

	if (tag == 0)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
	}
}