#include "StartGameViewDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameEventsFactory.h"
#include "GameKeyWithSuffixSupporter.h"

using namespace std;
using namespace cocos2d;

const float startXMenuPosition = 23.7;
const float startYMenuPosition = 23.7;
const float menuItemOffsetY = 23.7;

StartGameViewDataSource::StartGameViewDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource)
{

	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_menuItems = makeMenuItems();

}


StartGameViewDataSource::~StartGameViewDataSource()
{
}

vector <MenuItemInformation> StartGameViewDataSource::makeMenuItems() 
{

	vector <MenuItemInformation> menuItems = vector <MenuItemInformation>();

	if (_currentPlayerDataSource->isThereCurentPlayer)
	{
		MenuItemInformation menuItem1;
	    menuItem1.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kSelectLevel);
		GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(menuItem1,gameElement2Key);
		menuItems.push_back(menuItem1);
	}

	MenuItemInformation menuItem2;
	menuItem2.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kSelectLevel);
	GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(menuItem2,gameElement3Key);
    menuItems.push_back(menuItem2);

	MenuItemInformation menuItem3;
	menuItem3.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kRecords);
	GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(menuItem3,gameElement4Key);
    menuItems.push_back(menuItem3);

	MenuItemInformation menuItem4;
	menuItem4.gameEvent = GameEventsFactory::makeGoToPopUpEventWithKey(kRegulateSoundPopUp);
	GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(menuItem4,gameElement5Key);
    menuItems.push_back(menuItem4);

	MenuItemInformation menuItem5;
	menuItem5.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kDevelopers);
	GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(menuItem5,gameElement6Key);
    menuItems.push_back(menuItem5);
	
	return menuItems;

}

int StartGameViewDataSource::getMenuItemsCount()
{
	return _menuItems.size();
}

string StartGameViewDataSource::getMenuItemUnselectedImageForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.unselectedImage;
}

string StartGameViewDataSource::getMenuItemSelectedImageForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.selectedImage;
}

Vec2 StartGameViewDataSource::getMenuItemPositionForIndex(int aIndex)
{
	Vec2 position = Vec2(startXMenuPosition, startYMenuPosition + (menuItemOffsetY * aIndex));
	return position;
}

GameEvent StartGameViewDataSource::getMenuItemEventForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.gameEvent;
}

void StartGameViewDataSource::refreshDataSource()
{
	_menuItems = makeMenuItems();
}