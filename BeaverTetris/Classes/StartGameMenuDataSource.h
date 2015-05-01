#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include <functional>
#include "cocos2d.h"
#include "GameStructures.h"
#include "CurrentPlayerDataSource.h"

class StartGameMenuDataSource :public ServiceInterface
{
public:
	StartGameMenuDataSource();
	~StartGameMenuDataSource();

	int getMenuItemsCount();
	std::string getMenuInactiveImageForIndex(int aIndex);
	std::string getMenuActiveImageForIndex(int aIndex);
	cocos2d::Vec2 getMenuItemPositionForIndex(int aIndex);
	std::string getButtonTextForIndex(int aIndex);
	float getButtonTextRotationForIndex(int aIndex);
	std::function<void()> getMenuItemCallbackForIndex(int aIndex);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	std::vector <StartGameMenuItemInformation> _menuItems;

	std::vector <StartGameMenuItemInformation> makeMenuItems();

};

