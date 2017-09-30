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
	void createAnimation();
	CC_SYNTHESIZE(int, levelNum, LevelNum);
	CC_SYNTHESIZE(int, starNum, StarNum);
	int readGameIndexFromFile();
	void writeGameIndexToFile();

private:
	static GameManager* instance;

};

