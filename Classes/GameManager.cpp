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
