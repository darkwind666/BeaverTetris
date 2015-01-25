#pragma once

#include "cocos2d.h"
#include <vector>

class Node;

class PlayerActionControllerFactory
{
public:
	PlayerActionControllerFactory(void);
	~PlayerActionControllerFactory(void);

	cocos2d::Node* getPlayerActionControllerForCurrentPlatform();

private:

	std::vector<int> _platformsForDesktop;

	std::vector<int> getPlatformsForDesktop();

};

