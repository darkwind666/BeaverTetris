#pragma once

#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class EndGameViewDataSource
{
public:
	EndGameViewDataSource(void);
	~EndGameViewDataSource(void);

	int getMenuItemCount(void);
	std::string getMenuItemImageForIndex(int aIndex);
	cocos2d::Vec2 getMenuItemPositionForIndex(int aIndex);

	std::string getGameResultImage(void);
	cocos2d::Vec2  getGameResultImagePosition(void);

	bool getGameResult(void);

	void setGameResult(bool winGame);

};

