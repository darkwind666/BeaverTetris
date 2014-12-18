#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "cocos2d.h"
#include "GameStructures.h"
#include "CurrentPlayerDataSource.h"

class StartGameViewDataSource :public ServiceInterface
{
public:
	StartGameViewDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource);
	~StartGameViewDataSource();

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

};

