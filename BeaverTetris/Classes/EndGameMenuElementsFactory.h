#pragma once

#include "cocos2d.h"
#include <vector>

class EndGameMenuElementsCollectionCreator;

class EndGameMenuElementsFactory
{
public:
	EndGameMenuElementsFactory(void);
	~EndGameMenuElementsFactory(void);

	std::vector<cocos2d::Node*> getEndGameViewElements();

private:

	EndGameMenuElementsCollectionCreator *_endGameMenuElementsCreator;

	std::vector<cocos2d::Node*> getWinGameElements();
	
};

