#pragma once

#include "cocos2d.h"
#include <vector>
#include "GameEnums.h"
#include <functional>

class EndGameMenuElementCreator;

class EndGameMenuElementsCollectionCreator
{
public:
	EndGameMenuElementsCollectionCreator(void);
	~EndGameMenuElementsCollectionCreator(void);

	std::vector<cocos2d::Node*> getLoseGameElements();
	std::vector<cocos2d::Node*> getFinalLevelElements();
	std::vector<cocos2d::Node*> getNextLevelElements();

private:

	EndGameMenuElementCreator *_endGameMenuElementCreator;

	cocos2d::ccMenuCallback getGoToSceneCallback(GameState aState);

};

