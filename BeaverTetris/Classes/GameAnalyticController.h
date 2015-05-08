#pragma once

#include "ServiceInterface.h"
#include <string>
#include <map>
#include <functional>
#include "GameEnums.h"
#include "cocos2d.h"

class GoogleAnalyticIndicatorsDataSource;
class CurrentPlayerDataSource;
class GATrackerpp;

class GameAnalyticController : public ServiceInterface
{
public:
	GameAnalyticController(void);
	~GameAnalyticController(void);

	void startGame();
	void createdNewPlayerWithName(std::string aName);
	void winAllGameWithResult(int aResult);
	void winSelectedLevel();
	void loseSelectedLevel();
	void useSpell(std::string aSpellKey);
	void goToPopUp(PopUpType aPopUp);
	void goToScreen(GameState aScreen);

private:

	GoogleAnalyticIndicatorsDataSource *_indicatorsNamesDataSource;
	std::string _playerId;
	GATrackerpp *_analyticHelper;
	std::map< GameState, std::function<void()> > _screensAnalyticMessages;
	std::map<PopUpType, std::string> _popUpNames;
	std::map<cocos2d::Application::Platform, std::string > _platformsNames;

	std::map<cocos2d::Application::Platform, std::string> getPlatformsNames();
	std::map< GameState, std::function<void()> > getScreensAnalyticMessages();
	std::map<PopUpType, std::string> getPopUpNames();
	std::string getIndicator(std::string aKey);
	std::string getCurrentGameLanguage();
	std::string getOperationSystem();
	CurrentPlayerDataSource* getCurrentPlayerDataSource();

};

