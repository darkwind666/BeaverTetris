#include "GameAnalyticControllerDelegate.h"
#include "SerializersConstants.h"
#include "GoogleAnalyticsKeys.h"
#include "guid.h"
#include "GoogleAnalyticIndicatorsDataSource.h"

using namespace std;
using namespace cocos2d;

GameAnalyticControllerDelegate::GameAnalyticControllerDelegate(void)
{
	_indicatorsNamesDataSource = new GoogleAnalyticIndicatorsDataSource();
	_platformsNames = getPlatformsNames();
}


GameAnalyticControllerDelegate::~GameAnalyticControllerDelegate(void)
{
	delete _indicatorsNamesDataSource;
}

map<Application::Platform, string> GameAnalyticControllerDelegate::getPlatformsNames()
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

map<PopUpType, string> GameAnalyticControllerDelegate::getPopUpNames()
{
	map<PopUpType, string> popUpNames;

	popUpNames[kRegulateSoundPopUp] = gamePopUpSettingsActionKey;
	popUpNames[kPlayerCreatorPopUp] = gamePopUpCreateNewPlayerActionKey;
	popUpNames[kPauseGamePopUp] = gamePopUpPauseActionKey;

	return popUpNames;
}

string GameAnalyticControllerDelegate::getPlayerId()
{
	ValueMap playerIdData = getPlayerData();
	string playerId = playerIdData[playerIdKey].asString();
	return playerId;
}

ValueMap GameAnalyticControllerDelegate::getPlayerData()
{
	FileUtils *fileUtils = FileUtils::sharedFileUtils();
	ValueMap playerIdData = fileUtils->getValueMapFromFile(playerIdFileNameKey);
	if (playerIdData.size() == 0)
	{
		playerIdData = ValueMap();
		playerIdData[playerIdKey] = string("36d991da-52d3-4fa2-a428-4897648fb5dd");
		string fullPath = fileUtils->getWritablePath() + playerIdFileNameKey;
		fileUtils->writeToFile(playerIdData, fullPath);
	}
	return playerIdData;
}

string GameAnalyticControllerDelegate::getCurrentGameLanguage()
{
	string currentGameLanguage = _indicatorsNamesDataSource->getIndicatorNameForKey(gameEnglishLanguageKey);
	LanguageType gameLanguage = Application::getInstance()->getCurrentLanguage();
	if (gameLanguage == LanguageType::RUSSIAN)
	{
		currentGameLanguage = _indicatorsNamesDataSource->getIndicatorNameForKey(gameRussianLanguageKey);
	}
	return currentGameLanguage;
}

string GameAnalyticControllerDelegate::getOperationSystem()
{
	Application::Platform platform = Application::getInstance()->getTargetPlatform();
	return _platformsNames[platform];
}

string GameAnalyticControllerDelegate::getShopName()
{
	ValueMap shopData = getShopData();
	string shop = shopData[shopKey].asString();
	return shop;
}

ValueMap GameAnalyticControllerDelegate::getShopData()
{
	FileUtils *fileUtils = FileUtils::sharedFileUtils();
	ValueMap shopData = fileUtils->getValueMapFromFile(shopFileNameKey);
	if (shopData.size() == 0)
	{
		shopData = ValueMap();
		shopData[shopKey] = string("UnknowShop");
		string fullPath = fileUtils->getWritablePath() + shopFileNameKey;
		fileUtils->writeToFile(shopData, fullPath);
	}
	return shopData;
}

string GameAnalyticControllerDelegate::getIndicator(string aKey)
{
	string indicatorName = _indicatorsNamesDataSource->getIndicatorNameForKey(aKey);
	return indicatorName;
}
