#include "StartGameMenuDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameStatesHelper.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameElementsDataHelper.h"

using namespace std;
using namespace cocos2d;

StartGameMenuDataSource::StartGameMenuDataSource()
{

	_currentPlayerDataSource = (CurrentPlayerDataSource*) ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_menuItems = makeMenuItems();

}


StartGameMenuDataSource::~StartGameMenuDataSource()
{
}

vector <StartGameMenuItemInformation> StartGameMenuDataSource::makeMenuItems() 
{

	vector <StartGameMenuItemInformation> menuItems = vector <StartGameMenuItemInformation>();

	if (_currentPlayerDataSource->isThereCurentPlayer())
	{
		StartGameMenuItemInformation menuItem1;
		menuItem1.imageKey = gameElement1Key;
		menuItem1.callback = [this]()
		{
			_currentPlayerDataSource->cleanPlayer();
			GameStatesHelper::goToScene(kSelectLevel);
		};
		menuItems.push_back(menuItem1);
	}

	StartGameMenuItemInformation menuItem2;
	menuItem2.imageKey = gameElement2Key;
	menuItem2.callback = [](){GameStatesHelper::goToScene(kSelectLevel);};
    menuItems.push_back(menuItem2);

	StartGameMenuItemInformation menuItem3;
	menuItem3.imageKey = gameElement3Key;
	menuItem3.callback = [](){GameStatesHelper::goToScene(kRecords);};
    menuItems.push_back(menuItem3);

	StartGameMenuItemInformation menuItem4;
	menuItem4.imageKey = gameElement4Key;
	menuItem4.callback = [](){GameStatesHelper::goToPopUp(kRegulateSoundPopUp);};
    menuItems.push_back(menuItem4);

	StartGameMenuItemInformation menuItem5;
	menuItem5.imageKey = gameElement5Key;
	menuItem5.callback = [](){GameStatesHelper::goToScene(kDevelopers);};
    menuItems.push_back(menuItem5);
	
	return menuItems;

}

int StartGameMenuDataSource::getMenuItemsCount()
{
	return _menuItems.size();
}

string StartGameMenuDataSource::getMenuImageForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return GameFileExtensionMaker::getGraphicWithExtension(item.imageKey);
}

Vec2 StartGameMenuDataSource::getMenuItemPositionForIndex(int aIndex)
{
	
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(startGameMenuKey);
	Vec2 position = Vec2(0, 0 - (offset.y * aIndex));
	return position;
}

function<void()> StartGameMenuDataSource::getMenuItemCallbackForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return item.callback;
}


