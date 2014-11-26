#include "StartGameMenuDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameEventsFactory.h"

using namespace std;
using namespace cocos2d;

const float startXMenuPosition = 23.7;
const float startYMenuPosition = 23.7;
const float menuItemOffsetY = 23.7;
const string selectedPrefix = string("Selected");
const string unselectedPrefix = string("Unselected");

StartGameMenuDataSource::StartGameMenuDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource)
{

	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_menuItems = makeMenuItems();

}


StartGameMenuDataSource::~StartGameMenuDataSource()
{
}

vector <MenuItemInformation> StartGameMenuDataSource::makeMenuItems() 
{

	vector <MenuItemInformation> menuItems = vector <MenuItemInformation>();

	if (_currentPlayerDataSource->isThereCurentPlayer)
	{
		MenuItemInformation menuItem1;
	    menuItem1.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kSelectLevel);
		passImagesToMenuItemInformationWithKey(menuItem1,gameElement2Key);
		menuItems.push_back(menuItem1);
	}

	MenuItemInformation menuItem2;
	menuItem2.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kSelectLevel);
	passImagesToMenuItemInformationWithKey(menuItem2,gameElement3Key);
    menuItems.push_back(menuItem2);

	MenuItemInformation menuItem3;
	menuItem3.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kRecords);
	passImagesToMenuItemInformationWithKey(menuItem3,gameElement4Key);
    menuItems.push_back(menuItem3);

	MenuItemInformation menuItem4;
	menuItem4.gameEvent = GameEventsFactory::makeGoToPopUpEventWithKey(kRegulateSoundPopUp);
	passImagesToMenuItemInformationWithKey(menuItem4,gameElement5Key);
    menuItems.push_back(menuItem4);

	MenuItemInformation menuItem5;
	menuItem5.gameEvent = GameEventsFactory::makeGoToSceneEventWithKey(kDevelopers);
	passImagesToMenuItemInformationWithKey(menuItem5,gameElement6Key);
    menuItems.push_back(menuItem5);
	
	return menuItems;

}

void StartGameMenuDataSource::passImagesToMenuItemInformationWithKey(MenuItemInformation &aMenuItemInformation, string aKey)
{
	aMenuItemInformation.selectedImage = makeSelectedImageForKey(gameElement6Key);
	aMenuItemInformation.unselectedImage = makeUnselectedImageForKey(gameElement6Key);
}

string StartGameMenuDataSource::makeSelectedImageForKey(string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey + selectedPrefix);
}

string StartGameMenuDataSource::makeUnselectedImageForKey(string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey + unselectedPrefix);
}



int StartGameMenuDataSource::getMenuItemsCount()
{
	return _menuItems.size();
}

string StartGameMenuDataSource::getMenuItemUnselectedImageForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.unselectedImage;
}

string StartGameMenuDataSource::getMenuItemSelectedImageForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.selectedImage;
}

Vec2 StartGameMenuDataSource::getMenuItemPositionForIndex(int aIndex)
{
	Vec2 position = Vec2(startXMenuPosition, startYMenuPosition + (menuItemOffsetY * aIndex));
	return position;
}

GameEvent StartGameMenuDataSource::getMenuItemEventForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.gameEvent;
}

void StartGameMenuDataSource::refreshDataSource()
{
	_menuItems = makeMenuItems();
}