#include "GameScene.h"
#include "StartScene.h"
#include "GameManager.h"
#include "GameoverLayer.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!BaseLayer::init())
		return false;



	return true;
}