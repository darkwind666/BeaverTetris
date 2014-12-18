#include "EndGameViewDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameEventsFactory.h"
#include "GameKeyWithSuffixSupporter.h"


using namespace std;
using namespace cocos2d;

const float startXMenuPosition = 23.7f;
const float startYMenuPosition = 23.7f;
const float menuItemOffsetY = 23.7f;

EndGameViewDataSource::EndGameViewDataSource(CurrentLevelWinResultDataSource *aCurrentLevelWinResultDataSource, CurrentLevelDataSource *aCurrentLevelDataSource)
{
	_currentLevelWinResultDataSource = aCurrentLevelWinResultDataSource;
	_currentLevelDataSource = aCurrentLevelDataSource;
	_gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	refreshDataSource();
}

vector <MenuItemInformation> EndGameViewDataSource::makeMenuItems()
{
	vector <MenuItemInformation> menuItems = vector <MenuItemInformation>();
	
	MenuItemInformation goToSelectLevelMenuItem;
	goToSelectLevelMenuItem.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kSelectLevel);
	GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(goToSelectLevelMenuItem,gameElement3Key);
	menuItems.push_back(goToSelectLevelMenuItem);
	
	MenuItemInformation replayMenuItem;
	replayMenuItem.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kPlayGame);
	GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(replayMenuItem,gameElement4Key);
	menuItems.push_back(replayMenuItem);
	
	bool winCurrentGame  = getGameResult();
	bool winAllGames = _currentLevelWinResultDataSource->winAllGameResult();

	if (winCurrentGame && !winAllGames)
	{
		MenuItemInformation nextGameMenuItem;
		GameEvent nextGameMenuItemGameEvent;
		nextGameMenuItemGameEvent.eventType = kGoToNextLevelSceneEvent;
		nextGameMenuItem.gameEvent = nextGameMenuItemGameEvent;
		GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(nextGameMenuItem,gameElement5Key);
		menuItems.push_back(nextGameMenuItem);
	}
	
	return menuItems;
}

EndGameViewDataSource::~EndGameViewDataSource(void)
{
}

int EndGameViewDataSource::getMenuItemCount(void)
{
	return _menuItems.size();
}

string EndGameViewDataSource::getMenuItemImageForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.selectedImage;
}

Vec2 EndGameViewDataSource::getMenuItemPositionForIndex(int aIndex)
{
	Vec2 position = Vec2(startXMenuPosition, startYMenuPosition + (menuItemOffsetY * aIndex));
	return position;
}

string EndGameViewDataSource::getGameResultImage(void)
{
	string gameResultImage;

	if (getGameResult())
	{
		gameResultImage = GameFileExtensionMaker::getGraphicWithExtension(winGameKey);
	}
	else
	{
		gameResultImage = GameFileExtensionMaker::getGraphicWithExtension(loseGameKey);
	}
	return gameResultImage;
}

Vec2  EndGameViewDataSource::getGameResultImagePosition(void)
{
	return _gameViewElementsDataSource->getElementPositionForKey(gameResultKey);
}

int EndGameViewDataSource::getGameAward(void)
{
	return _currentLevelWinResultDataSource->getCurrentLevelAward();
}

Vec2  EndGameViewDataSource::getGameAvardLabelPosition(void)
{
	return _gameViewElementsDataSource->getElementPositionForKey(gameAwardKey);
}

bool EndGameViewDataSource::getGameResult(void)
{
	return _currentLevelWinResultDataSource->winGameResult();
}

void EndGameViewDataSource::refreshDataSource()
{
	_menuItems = makeMenuItems();
}





