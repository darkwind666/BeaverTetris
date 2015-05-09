#pragma once

#include <string>
#include <map>
#include "GameEnums.h"
#include "cocos2d.h"

class GoogleAnalyticIndicatorsDataSource;

class GameAnalyticControllerDelegate
{
public:
	GameAnalyticControllerDelegate(void);
	~GameAnalyticControllerDelegate(void);

	std::string getPlayerId();
	std::string getCurrentGameLanguage();
	std::string getOperationSystem();
	std::string getShopName();
	std::map<PopUpType, std::string> getPopUpNames();
	std::string getIndicator(std::string aKey);

private:

	GoogleAnalyticIndicatorsDataSource *_indicatorsNamesDataSource;
	std::map<cocos2d::Application::Platform, std::string > _platformsNames;

	std::map<cocos2d::Application::Platform, std::string> getPlatformsNames();
	cocos2d::ValueMap getPlayerData();
	cocos2d::ValueMap getShopData();

};

