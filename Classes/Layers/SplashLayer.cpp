#include "SplashLayer.h"


SplashLayer::SplashLayer()
{
}


SplashLayer::~SplashLayer()
{
}

Scene* SplashLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SplashLayer::create();
	scene->addChild(layer);

	return scene;
}

bool SplashLayer::init()
{
	if (!BaseLayer::init())
		return false;




	return true;
}