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
class GameAnalyticControllerDelegate;

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

	GameAnalyticControllerDelegate *_analyticDelegate;
	std::string _playerId;
	std::string _shopName;
	std::string _language;
	std::string _operationSystem;
	GATrackerpp *_analyticHelper;
	std::map< GameState, std::function<void()> > _screensAnalyticMessages;
	std::map<PopUpType, std::string> _popUpNames;

	std::map< GameState, std::function<void()> > getScreensAnalyticMessages();
	std::string getIndicator(std::string aKey);
	CurrentPlayerDataSource* getCurrentPlayerDataSource();

};

