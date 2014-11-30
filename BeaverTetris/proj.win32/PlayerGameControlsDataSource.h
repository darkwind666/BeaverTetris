#pragma once

#include <string>
#include <vector>
#include "cocos2d.h"
#include "GameStructures.h"
#include "GameViewElementsDataSource.h"

class PlayerGameControlsDataSource
{
public:
	PlayerGameControlsDataSource(GameViewElementsDataSource *aGameViewElementsDataSource);
	~PlayerGameControlsDataSource(void);

	int getPlayerControlsCount();
	std::string getPlayerControlIconImageOnIndex(int aIndex);
	cocos2d::Vec2 getPlayerControlPositionOnIndex(int aIndex);
	GameEvent getPlayerControlEventOnIndex(int aIndex);

private:

	GameViewElementsDataSource *_gameViewElementsDataSource;
	std::vector<PlayerControllInformation> _playerControls;

	std::vector<PlayerControllInformation> getPlayerControls();

};

