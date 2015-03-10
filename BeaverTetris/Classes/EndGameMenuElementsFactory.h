#pragma once

#include "cocos2d.h"
#include <vector>
#include <string>
#include "GameEnums.h"
#include <functional>

class EndGameMenuElementsFactory
{
public:
	EndGameMenuElementsFactory(void);
	~EndGameMenuElementsFactory(void);

	std::vector<cocos2d::Node*> getEndGameViewElements();

private:

	std::vector<cocos2d::Node*> getWinGameElements();
	std::vector<cocos2d::Node*> getLoseGameElements();
	std::vector<cocos2d::Node*> getFinalLevelElements();
	std::vector<cocos2d::Node*> getNextLevelElements();

	cocos2d::Node* getGameStateLabelWithString(std::string stateLabelString);
	cocos2d::Node* getButtonWithCallbackAndColor(std::function<void()> aCallback, cocos2d::ccColor3B aColor);
	cocos2d::Node* getPlayerAwardLabel();
	std::function<void()> getNextLevelCallback();
	std::function<void()> getGoToSceneCallback(GameState aState);
};

