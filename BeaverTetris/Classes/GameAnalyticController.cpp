#include "GameAnalyticController.h"
#include "GoogleAnalyticIndicatorsDataSource.h"
#include "GoogleAnalyticsKeys.h"
#include "GATrackerpp.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "StringsSupporter.h"
#include "KeysForEnumsDataSource.h"

using namespace std;
using namespace cocos2d;

GameAnalyticController::GameAnalyticController(void)
{
	_indicatorsNamesDataSource = new GoogleAnalyticIndicatorsDataSource();
	_playerId = string("71798b3b-97af-433e-a83a-fc95f95e50f5");
	_analyticHelper = new GATrackerpp("UA-61796273-1", _playerId, string("BeaverTetris"), string("v1"));
	_platformsNames = getPlatformsNames();
	_screensAnalyticMessages = getScreensAnalyticMessages();
	_popUpNames = getPopUpNames();
}


GameAnalyticController::~GameAnalyticController(void)
{
	_analyticHelper->sendEndAppView(getIndicator(gameExitScreenAnalyticKey));
	delete _indicatorsNamesDataSource;
}

map<Application::Platform, string> GameAnalyticController::getPlatformsNames()
{
	map<Application::Platform, string> platformsNames;

	platformsNames[Application::Platform::OS_WINDOWS] = string("Windows");
	platformsNames[Application::Platform::OS_LINUX] = string("Linux");
	platformsNames[Application::Platform::OS_MAC] = string("MacOS");
	platformsNames[Application::Platform::OS_ANDROID] = string("Android");
	platformsNames[Application::Platform::OS_IPHONE] = string("Iphone");
	platformsNames[Application::Platform::OS_IPAD] = string("Ipad");
	platformsNames[Application::Platform::OS_BLACKBERRY] = string("Blackberry");
	platformsNames[Application::Platform::OS_TIZEN] = string("Tizen");
	platformsNames[Application::Platform:: OS_NACL] = string("ChromeOs");
	platformsNames[Application::Platform::OS_WINRT] = string("WindowsRT");
	platformsNames[Application::Platform::OS_WP8] = string("WindowsPhone");

	return platformsNames;
}

map< GameState, function<void()> > GameAnalyticController::getScreensAnalyticMessages()
{
	map< GameState, function<void()> > screensAnalyticMessages;

	screensAnalyticMessages[kStartGame] = [this](){_analyticHelper->sendAppView(getIndicator(mainGameMenuScreenAnalyticKey));};
	screensAnalyticMessages[kSelectLevel] = [this](){_analyticHelper->sendAppView(getIndicator(selectGameLevelScreenAnalyticKey));};
	screensAnalyticMessages[kDevelopers] = [this](){_analyticHelper->sendAppView(getIndicator(gameDevelopersScreenAnalyticKey));};
	screensAnalyticMessages[kRecords] = [this](){_analyticHelper->sendAppView(getIndicator(gameRecordsScreenAnalyticKey));};

	screensAnalyticMessages[kLoadGame] = [this](){
		string shopName = string("SashaShop");
		string language = getCurrentGameLanguage();
		_analyticHelper->sendStartAppView(getIndicator(loadingScreenAnalyticKey), shopName, language);
		_analyticHelper->sendEvent(getIndicator(commonAnalyticCategoryKey), getIndicator(operationSystemKey), getOperationSystem());
	};

	screensAnalyticMessages[kPlayGame] = [this](){
		int selectedLevel = getCurrentPlayerDataSource()->getSelectedGameLevelIndex();
		string levelIndex = StringsSupporter::getStringFromNumber(selectedLevel + 1);
		_analyticHelper->sendAppView(getIndicator(levelKey) + levelIndex);
	};

	return screensAnalyticMessages;
}

string GameAnalyticController::getCurrentGameLanguage()
{
	string currentGameLanguage = _indicatorsNamesDataSource->getIndicatorNameForKey(gameEnglishLanguageKey);
	LanguageType gameLanguage = Application::getInstance()->getCurrentLanguage();
	if (gameLanguage == LanguageType::RUSSIAN)
	{
		currentGameLanguage = _indicatorsNamesDataSource->getIndicatorNameForKey(gameRussianLanguageKey);
	}
	return currentGameLanguage;
}

string GameAnalyticController::getOperationSystem()
{
	Application::Platform platform = Application::getInstance()->getTargetPlatform();
	return _platformsNames[platform];
}

map<PopUpType, string> GameAnalyticController::getPopUpNames()
{
	map<PopUpType, string> popUpNames;

	popUpNames[kRegulateSoundPopUp] = gamePopUpSettingsActionKey;
	popUpNames[kPlayerCreatorPopUp] = gamePopUpCreateNewPlayerActionKey;
	popUpNames[kPauseGamePopUp] = gamePopUpPauseActionKey;

	return popUpNames;
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
	string indicatorName = _indicatorsNamesDataSource->getIndicatorNameForKey(aKey);
	return indicatorName;
}

CurrentPlayerDataSource* GameAnalyticController::getCurrentPlayerDataSource()
{
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	return currentPlayerDataSource;
}

