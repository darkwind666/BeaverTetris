#pragma once

#include "cocos2d.h"
#include <vector>

class Node;

class PlayerSpellsControllerFactory
{
public:
	PlayerSpellsControllerFactory(void);
	~PlayerSpellsControllerFactory(void);

	cocos2d::Node* getPlayerSpellsControllerForCurrentPlatform();

private:

	std::vector<int> _platformsForDesktop;

	std::vector<int> getPlatformsForDesktop();

};

