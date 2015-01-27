#pragma once

#include <string>
#include <vector>
#include <functional>
#include "cocos2d.h"
#include "GameStructures.h"

class GameViewElementsDataSource;
class CurrentDetailController;

class PlayerGameControlsDataSource
{
public:
	PlayerGameControlsDataSource();
	~PlayerGameControlsDataSource(void);

	int getPlayerControlsCount();
	std::string getPlayerControlIconImageOnIndex(int aIndex);
	cocos2d::Vec2 getPlayerControlPositionOnIndex(int aIndex);
	int  getPlayerControlKeyboardKeyOnIndex(int aIndex);
	std::function<void()> getPlayerControlCallbackForIndex(int aIndex);

private:

	GameViewElementsDataSource *_gameViewElementsDataSource;
	CurrentDetailController *_currentDetailController;
	std::vector<PlayerControllInformation> _playerControls;

	std::vector<PlayerControllInformation> getPlayerControls();

};

