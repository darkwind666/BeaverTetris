#pragma once

#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "GameEnums.h"
#include "GameDesignConstants.h"


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
	PlayerActionInGameType playerAction;
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

struct GamePositionOnBoard
{
	int xPosition;
	int yPosition;
	
};

struct PlayerControllInformation
{
	std::string controlKey;
	GameEvent controlEvent;
	
};

struct GameLevelInformation
{
	std::string levelName;
	int levelAward;
	std::vector<TetraminoType> availableTetraminos;
	std::vector<TetraminoDetailType> availableTetraminoDetails;
	std::vector<TetraminoType> availableBosses;
};

struct TetraminoDetailInformation
{
	bool rotateble;
	int tetraminoElements[standartDetailWidth][standartDetailHeight];
};

struct SpellInformation
{
	SpellType spellType;
	std::string spellName;
	int spellCost;
};







