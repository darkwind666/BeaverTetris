#pragma once

#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "GameEnums.h"

struct ViewElementInformation
{
	std::string elementImage;
	cocos2d::Vec2 elementPosition;
	int elementZOrder;

};

struct PlayerInformation
{
	std::string elementImage;
	int playerScore;
};

struct GameEvent
{
	std::string eventName;
	GameEventInformation eventInformation;
};

struct GameEventInformation
{
	GameState gameState;
};

struct MenuItemInformation
{
	std::string unselectedImage;
	std::string selectedImage;
	cocos2d::Vec2 position;
	GameEvent gameEvent;
};

struct LevelInformation
{
	std::vector <TetraminoType> gameTetraminos;
	VictoryConditionType victoryCondition;
	VictoryConditionInformation victoryDetails;
	int rewardSum;
	SpellType addSpell;
	
};

struct VictoryConditionInformation
{
	int detailsCount;
	int time;
	std::map <TetraminoType, int> gameTetraminos;
};




