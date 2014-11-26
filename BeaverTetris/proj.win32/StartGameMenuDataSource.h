#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "cocos2d.h"
#include "GameStructures.h"
#include "CurrentPlayerDataSource.h"

class StartGameMenuDataSource :public ServiceInterface
{
public:
	StartGameMenuDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource);
	~StartGameMenuDataSource();

	int getMenuItemsCount();
	std::string getMenuItemUnselectedImageForIndex(int aIndex);
	std::string getMenuItemSelectedImageForIndex(int aIndex);
	cocos2d::Vec2 getMenuItemPositionForIndex(int aIndex);
	GameEvent getMenuItemEventForIndex(int aIndex);

	void refreshDataSource();


private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	std::vector <MenuItemInformation> _menuItems;

	vector <MenuItemInformation> makeMenuItems();
	std::string makeSelectedImageForKey(std::string aKey);
	std::string makeUnselectedImageForKey(std::string aKey);
	void passImagesToMenuItemInformationWithKey(MenuItemInformation &aMenuItemInformation, string aKey);

};

