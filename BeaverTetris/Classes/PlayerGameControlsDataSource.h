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
	cocos2d::Vec2 getPlayerControlPositionOnIndex(int aIndex);
	float getPlayerControlRotationForIndex(int aIndex);
	int  getPlayerControlKeyboardKeyOnIndex(int aIndex);
	std::function<void()> getPlayerControlCallbackForIndex(int aIndex);
	std::string getPlayerControlImageForIndex(int aIndex);

private:

	GameViewElementsDataSource *_gameViewElementsDataSource;
	CurrentDetailController *_currentDetailController;
	std::vector<PlayerControllInformation> _playerControls;

	std::vector<PlayerControllInformation> getPlayerControls();

};

