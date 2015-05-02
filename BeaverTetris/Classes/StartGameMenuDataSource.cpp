#include "StartGameMenuDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameStatesHelper.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameKeyWithSuffixSupporter.h"
#include "GameViewElementsDataSource.h"
#include "StringsSupporter.h"
#include "GameLocalizationKeys.h"

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
		StartGameMenuItemInformation menuItem2;
		menuItem2.imageKey = selectGameLevelButtonKey;
		menuItem2.textRotation = -10.0f;
		menuItem2.text = StringsSupporter::getLocalizedStringFromKey(selectLevelLocalizationKey);
		menuItem2.callback = [](){GameStatesHelper::goToScene(kSelectLevel);};
		menuItems.push_back(menuItem2);
	}

	StartGameMenuItemInformation menuItem1;
	menuItem1.imageKey = createNewGameButtonKey;
	menuItem1.textRotation = 0;
	menuItem1.text = StringsSupporter::getLocalizedStringFromKey(newGameLocalizationKey);
	menuItem1.callback = [this]()
	{
		_currentPlayerDataSource->cleanPlayer();
		GameStatesHelper::goToScene(kSelectLevel);
	};
	menuItems.push_back(menuItem1);

	StartGameMenuItemInformation menuItem3;
	menuItem3.imageKey = goToGameRecordsButtonKey;
	menuItem3.textRotation = -13.0f;
	menuItem3.text = StringsSupporter::getLocalizedStringFromKey(gameRecordsLocalizationKey);
	menuItem3.callback = [](){GameStatesHelper::goToScene(kRecords);};
    menuItems.push_back(menuItem3);

	StartGameMenuItemInformation menuItem4;
	menuItem4.imageKey = getSoundRegulatorsButtonKey;
	menuItem4.textRotation = -13.0f;
	menuItem4.text = StringsSupporter::getLocalizedStringFromKey(gameSettingsLocalizationKey);
	menuItem4.callback = [](){GameStatesHelper::goToPopUp(kRegulateSoundPopUp);};
    menuItems.push_back(menuItem4);

	StartGameMenuItemInformation menuItem5;
	menuItem5.imageKey = goToDevelopersButtonKey;
	menuItem5.textRotation = -10.0f;
	menuItem5.text = StringsSupporter::getLocalizedStringFromKey(gameDevelopersLocalizationKey);
	menuItem5.callback = [](){GameStatesHelper::goToScene(kDevelopers);};
    menuItems.push_back(menuItem5);
	
	return menuItems;

}

int StartGameMenuDataSource::getMenuItemsCount()
{
	return _menuItems.size();
}

string StartGameMenuDataSource::getMenuInactiveImageForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return GameKeyWithSuffixSupporter::makeUnselectedImageForKey(item.imageKey);
}

string StartGameMenuDataSource::getMenuActiveImageForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return GameKeyWithSuffixSupporter::makeSelectedImageForKey(item.imageKey);
}

Vec2 StartGameMenuDataSource::getMenuItemPositionForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	GameViewElementsDataSource *gameViewElementsDataSource = (GameViewElementsDataSource*) ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	Vec2 position = gameViewElementsDataSource->getElementPositionForKey(item.imageKey);
	return position;
}

float StartGameMenuDataSource::getButtonTextRotationForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return item.textRotation;
}

string StartGameMenuDataSource::getButtonTextForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return item.text;
}

function<void()> StartGameMenuDataSource::getMenuItemCallbackForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return item.callback;
}


