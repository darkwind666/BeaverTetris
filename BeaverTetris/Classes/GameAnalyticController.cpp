#include "GameAnalyticController.h"
#include "GoogleAnalyticIndicatorsDataSource.h"
#include "GoogleAnalyticsKeys.h"
#include "GATrackerpp.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "StringsSupporter.h"
#include "KeysForEnumsDataSource.h"
#include "GameAnalyticControllerDelegate.h"

using namespace std;
using namespace cocos2d;

GameAnalyticController::GameAnalyticController(void)
{
	_analyticDelegate = new GameAnalyticControllerDelegate();
	_shopName = _analyticDelegate->getShopName();
	_language = _analyticDelegate->getCurrentGameLanguage();
	_operationSystem = _analyticDelegate->getOperationSystem();
	_playerId = _analyticDelegate->getPlayerId();
	_analyticHelper = new GATrackerpp("UA-62798008-1", _playerId, string("BeaverTetris"), string("v1"));
	_screensAnalyticMessages = getScreensAnalyticMessages();
	_popUpNames = _analyticDelegate->getPopUpNames();
}


GameAnalyticController::~GameAnalyticController(void)
{
	_analyticHelper->sendEndAppView(getIndicator(gameExitScreenAnalyticKey));
	delete _analyticDelegate;
}

map< GameState, function<void()> > GameAnalyticController::getScreensAnalyticMessages()
{
	map< GameState, function<void()> > screensAnalyticMessages;

	screensAnalyticMessages[kStartGame] = [this](){_analyticHelper->sendAppView(getIndicator(mainGameMenuScreenAnalyticKey));};
	screensAnalyticMessages[kSelectLevel] = [this](){_analyticHelper->sendAppView(getIndicator(selectGameLevelScreenAnalyticKey));};
	screensAnalyticMessages[kDevelopers] = [this](){_analyticHelper->sendAppView(getIndicator(gameDevelopersScreenAnalyticKey));};
	screensAnalyticMessages[kRecords] = [this](){_analyticHelper->sendAppView(getIndicator(gameRecordsScreenAnalyticKey));};

	screensAnalyticMessages[kLoadGame] = [this](){
		_analyticHelper->sendStartAppView(getIndicator(loadingScreenAnalyticKey), _shopName, _language);
		_analyticHelper->sendEvent(getIndicator(commonAnalyticCategoryKey), getIndicator(operationSystemKey), _operationSystem);
	};

	screensAnalyticMessages[kPlayGame] = [this](){
		int selectedLevel = getCurrentPlayerDataSource()->getSelectedGameLevelIndex();
		string levelIndex = StringsSupporter::getStringFromNumber(selectedLevel + 1);
		_analyticHelper->sendAppView(getIndicator(levelKey) + levelIndex);
	};

	return screensAnalyticMessages;
}

void GameAnalyticController::startGame()
{
	goToScreen(kLoadGame);
}

void GameAnalyticController::createdNewPlayerWithName(string aName)
{
	_analyticHelper->sendEvent(getIndicator(commonAnalyticCategoryKey), getIndicator(createNewGamePlayerActionKey), aName);
}

void GameAnalyticController::winAllGameWithResult(int aResult)
{
	_analyticHelper->sendEvent(getIndicator(commonAnalyticCategoryKey), getIndicator(compliteAllGameActionKey), _playerId, aResult);
}

void GameAnalyticController::winSelectedLevel()
{
	int selectedLevel = getCurrentPlayerDataSource()->getSelectedGameLevelIndex();
	string levelIndex = StringsSupporter::getStringFromNumber(selectedLevel + 1);
	int playerScore = getCurrentPlayerDataSource()->getPlayerScore();
	_analyticHelper->sendEvent(getIndicator(winLevelAnalyticCategoryKey), getIndicator(levelKey) + levelIndex, playerScore);
}

void GameAnalyticController::loseSelectedLevel()
{
	int selectedLevel = getCurrentPlayerDataSource()->getSelectedGameLevelIndex();
	string levelIndex = StringsSupporter::getStringFromNumber(selectedLevel + 1);
	_analyticHelper->sendEvent(getIndicator(loseLevelAnalyticCategoryKey), getIndicator(levelKey) + levelIndex);
}

void GameAnalyticController::useSpell(std::string aSpellKey)
{
	int selectedLevel = getCurrentPlayerDataSource()->getSelectedGameLevelIndex();
	string levelIndex = StringsSupporter::getStringFromNumber(selectedLevel + 1);
	KeysForEnumsDataSource *keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	SpellType spellType = keysForEnumsDataSource->getSpellTypeForKey(aSpellKey);
	string spellName = StringsSupporter::getStringFromNumber(spellType);
	_analyticHelper->sendEvent(getIndicator(spellUsingCategoryKey), getIndicator(levelKey) + levelIndex, getIndicator(spellKey) + spellName);
}

void GameAnalyticController::goToPopUp(PopUpType aPopUp)
{
	string popUpName = _popUpNames[aPopUp];
	_analyticHelper->sendEvent(getIndicator(gamePopUpsCategoryKey), getIndicator(popUpName));
}

void GameAnalyticController::goToScreen(GameState aScreen)
{
	map< GameState, function<void()> >::iterator screenIterator;
	screenIterator = _screensAnalyticMessages.find(aScreen);
	if (screenIterator != _screensAnalyticMessages.end())
	{
		function<void()> screenAnalyticMessage = screenIterator->second;
		screenAnalyticMessage();
	}
}

string GameAnalyticController::getIndicator(string aKey)
{
	string indicatorName = _analyticDelegate->getIndicator(aKey);
	return indicatorName;
}

CurrentPlayerDataSource* GameAnalyticController::getCurrentPlayerDataSource()
{
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	return currentPlayerDataSource;
}

