#include "PlayerSpellsControllerFactory.h"
#include "PlayerSpellsControllerDesktop.h"

using namespace cocos2d;
using namespace std;

PlayerSpellsControllerFactory::PlayerSpellsControllerFactory(void)
{
	_platformsForDesktop = getPlatformsForDesktop();
}


PlayerSpellsControllerFactory::~PlayerSpellsControllerFactory(void)
{
}

cocos2d::Node* PlayerSpellsControllerFactory::getPlayerSpellsControllerForCurrentPlatform()
{
	cocos2d::Node *playerController;
	vector<int>::iterator platformIterator = find(_platformsForDesktop.begin(), _platformsForDesktop.end(), CC_TARGET_PLATFORM);
	if (platformIterator != _platformsForDesktop.end())
	{
		playerController = new PlayerSpellsControllerDesktop();
	}
	else
	{

	}
	return playerController;
}

vector<int> PlayerSpellsControllerFactory::getPlatformsForDesktop()
{
	vector<int> platformsForDesktop;
	platformsForDesktop.push_back(CC_PLATFORM_WIN32);
	platformsForDesktop.push_back(CC_PLATFORM_LINUX);
	platformsForDesktop.push_back(CC_PLATFORM_MAC);
	return platformsForDesktop;
}