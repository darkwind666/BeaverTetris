#pragma once

#include "cocos2d.h"
#include <vector>

class EndGameMenuElementsFactory
{
public:
	EndGameMenuElementsFactory(void);
	~EndGameMenuElementsFactory(void);

	std::vector<cocos2d::Node*> getEndGameViewElements();

};

