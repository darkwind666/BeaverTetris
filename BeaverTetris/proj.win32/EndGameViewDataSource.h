#pragma once

#include <string>
#include <vector>
#include "cocos2d.h"
#include "GameStructures.h"
#include "CurrentLevelWinResultDataSource.h"
#include "CurrentLevelDataSource.h"
#include "GameViewElementsDataSource.h"

class EndGameViewDataSource
{
public:
	EndGameViewDataSource(CurrentLevelWinResultDataSource *aCurrentLevelWinResultDataSource, CurrentLevelDataSource *aCurrentLevelDataSource);
	~EndGameViewDataSource(void);

	int getMenuItemCount(void);
	std::string getMenuItemImageForIndex(int aIndex);
	cocos2d::Vec2 getMenuItemPositionForIndex(int aIndex);

	std::string getGameResultImage(void);
	cocos2d::Vec2  getGameResultImagePosition(void);
	int getGameAward(void);
	cocos2d::Vec2  getGameAvardLabelPosition(void);

	bool getGameResult(void);

	void refreshDataSource();

private:

	CurrentLevelWinResultDataSource *_currentLevelWinResultDataSource;
	CurrentLevelDataSource *_currentLevelDataSource;
	GameViewElementsDataSource *_gameViewElementsDataSource;
	std::vector <MenuItemInformation> _menuItems;
	
	std::vector <MenuItemInformation> makeMenuItems();

};

