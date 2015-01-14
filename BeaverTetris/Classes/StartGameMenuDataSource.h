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
	StartGameMenuDataSource();
	~StartGameMenuDataSource();

	int getMenuItemsCount();
	std::string getMenuImageForIndex(int aIndex);
	cocos2d::Vec2 getMenuItemPositionForIndex(int aIndex);
	void pressMenuItemForIndex(int aIndex);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	std::vector <StartGameMenuItemInformation> _menuItems;

	std::vector <StartGameMenuItemInformation> makeMenuItems();

};

