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

	cocos2d::Node* getGameStateLabelWithLocaleString(std::string aLocaleString);
	cocos2d::Node* getButtonWithCallbackAndKeyAndLocale(cocos2d::ccMenuCallback aCallback, std::string aKey, std::string aLocale);
	cocos2d::Node* getPlayerAwardLabel();
	cocos2d::ccMenuCallback getNextLevelCallback();
	cocos2d::ccMenuCallback getFinishGameCallback();
	cocos2d::ccMenuCallback getGoToSceneCallback(GameState aState);

};

