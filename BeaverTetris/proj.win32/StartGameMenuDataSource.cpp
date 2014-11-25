#include "StartGameMenuDataSource.h"

using namespace std;
using namespace cocos2d;

StartGameMenuDataSource::StartGameMenuDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource, GameViewElementsDataSource *aGameViewElementsDataSource)
{

	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_gameViewElementsDataSource = aGameViewElementsDataSource;
	_menuItems = std::vector <MenuItemInformation>();

}


StartGameMenuDataSource::~StartGameMenuDataSource()
{
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
	MenuItemInformation item = _menuItems[aIndex];
	return item.position;
}

GameEvent StartGameMenuDataSource::getMenuItemEventForIndex(int aIndex)
{
	MenuItemInformation item = _menuItems[aIndex];
	return item.gameEvent;
}

void StartGameMenuDataSource::refreshDataSource()
{
}