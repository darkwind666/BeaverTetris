#pragma once

#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "GameEnums.h"
#include "Tetramino.h"


struct ViewElementInformation
{
	std::string elementImage;
	cocos2d::Vec2 elementPosition;
	int elementZOrder;

};

struct PlayerInformation
{
	std::string playerName;
	int playerScore;
};

struct GameEventInformation
{
	GameState gameState;
	PopUpType popUp;
};

struct GameEvent
{
	EventType eventType;
	GameEventInformation eventInformation;
};

struct MenuItemInformation
{
	std::string unselectedImage;
	std::string selectedImage;
	cocos2d::Vec2 position;
	GameEvent gameEvent;
};

struct VictoryConditionInformation
{
	int detailsCount;
	int time;
	std::map <TetraminoType, int> gameTetraminos;
};

struct LevelInformation
{
	std::vector <TetraminoType> gameTetraminos;
	VictoryConditionType victoryCondition;
	VictoryConditionInformation victoryDetails;
	int rewardSum;
	SpellType addSpell;
	
};


struct TetraminoDetail
{
	Tetramino tetraminos[3][3];
	int positionX;
	int positionY;

};





