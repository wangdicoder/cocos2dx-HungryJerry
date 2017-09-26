#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameManager
{
public:
	GameManager();
	~GameManager();
	static GameManager* getInstance();
	void showFullScreenAd();
	void exitGame();

private:
	static GameManager* instance;

};

