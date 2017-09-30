#include "GameManager.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../android/jni/JniHelper.h"
#include "jni.h"
#endif

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

GameManager* GameManager::instance = NULL;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();

	return instance;
}

void GameManager::showFullScreenAd()
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "fullScreenAd", "()V");
		if (isHave)
		{
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
		}

	#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		

	#endif
}

void GameManager::exitGame()
{
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JniMethodInfo minfo;
		bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "exit", "()V");
		if (isHave)
		{
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
		}
	#endif
}

void GameManager::createAnimation()
{
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/mouse.plist");
		Vector<SpriteFrame*> frames;
		char str[50] = { 0 };
		for (int i = 1; i <= 6; i++)
		{
			sprintf(str, "mouse_normal_%d.png", i);
			frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
		}
		auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
		AnimationCache::getInstance()->addAnimation(animation, "eatingAnimation1");
	}
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/laser.plist");
		Vector<SpriteFrame*> frames;
		char str[50] = { 0 };
		for (int i = 0; i <= 3; i++)
		{
			sprintf(str, "laser%d.png", i);
			frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
		}
		auto animation = Animation::createWithSpriteFrames(frames, 0.04f, -1);
		AnimationCache::getInstance()->addAnimation(animation, "laser");
	}
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/start_mouse.plist");
		Vector<SpriteFrame*> frames;
		char str[50] = { 0 };
		for (int i = 0; i <= 8; i++)
		{
			sprintf(str, "menu_rata-sheet%d.png", i);
			frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
		}
		auto animation = Animation::createWithSpriteFrames(frames, 0.2f, -1);
		AnimationCache::getInstance()->addAnimation(animation, "mouse_home");
	}
}

void GameManager::writeGameIndexToFile()
{
	std::string fileName = FileUtils::getInstance()->getWritablePath() + "data";
	FILE *fp = NULL;

	if (fileName.length() > 0)
	{
		fp = fopen(fileName.c_str(), "w+");
		if (fp)
		{
			fprintf(fp, "%d", levelNum + 1);
			fclose(fp);
		}
	}
}

int GameManager::readGameIndexFromFile()
{
	std::string fileName = FileUtils::getInstance()->getWritablePath() + "data";
	FILE* fp = NULL;
	char strLine[5];
	int maxIndex = 1;

	if (fileName.length() > 0)
	{
		fp = fopen(fileName.c_str(), "r");
		if (fp)
		{
			fgets(strLine, 5, fp);
			maxIndex = Value(strLine).asInt();
			fclose(fp);
		}
	}

	return maxIndex;
}