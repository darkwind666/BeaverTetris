#include "PlayerActionControllerFactory.h"
#include "PlayerActionControllerDesktop.h"

using namespace cocos2d;
using namespace std;

PlayerActionControllerFactory::PlayerActionControllerFactory(void)
{
	_platformsForDesktop = getPlatformsForDesktop();
}


PlayerActionControllerFactory::~PlayerActionControllerFactory(void)
{
}

cocos2d::Node* PlayerActionControllerFactory::getPlayerActionControllerForCurrentPlatform()
{
	cocos2d::Node *playerController;
	vector<int>::iterator platformIterator = find(_platformsForDesktop.begin(), _platformsForDesktop.end(), CC_TARGET_PLATFORM);
	if (platformIterator != _platformsForDesktop.end())
	{
		playerController = new PlayerActionControllerDesktop();
	}
	else
	{

	}
	return playerController;
}

vector<int> PlayerActionControllerFactory::getPlatformsForDesktop()
{
	vector<int> platformsForDesktop;
	platformsForDesktop.push_back(CC_PLATFORM_WIN32);
	platformsForDesktop.push_back(CC_PLATFORM_LINUX);
	platformsForDesktop.push_back(CC_PLATFORM_MAC);
	platformsForDesktop.push_back(CC_PLATFORM_ANDROID);
	return platformsForDesktop;
}