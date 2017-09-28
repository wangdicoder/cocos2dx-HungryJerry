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
}
