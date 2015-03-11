#pragma once

#include "cocos2d.h"
#include <string>
#include "GameEnums.h"
#include <functional>

class EndGameMenuElementCreator
{
public:
	EndGameMenuElementCreator(void);
	~EndGameMenuElementCreator(void);

	cocos2d::Node* getGameStateLabelWithString(std::string stateLabelString);
	cocos2d::Node* getButtonWithCallbackAndColor(std::function<void()> aCallback, cocos2d::ccColor3B aColor);
	cocos2d::Node* getPlayerAwardLabel();
	std::function<void()> getNextLevelCallback();
	std::function<void()> getFinishGameCallback();
	std::function<void()> getGoToSceneCallback(GameState aState);

};

