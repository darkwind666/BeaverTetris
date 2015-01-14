#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "cocos2d.h"
#include "GameEnums.h"
#include "GameDesignConstants.h"

class ResourcesLoader;
struct ResoucesLoaderInformation
{
	int loadPercentage;
	ResourcesLoader *resourcesLoader;
};


struct StartGameMenuItemInformation
{
	std::string imageKey;
	std::function<void()> callback;
};


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

struct TetraminoBossesInformation
{
	TetraminoType aBossType;
	int bossesCount;
};

struct TetraminosForWinInformation
{
	TetraminoType tetraminoType;
	int tetraminosCount;
};

struct GameLevelInformation
{
	std::string levelName;
	int levelAward;
	std::vector<TetraminoType> availableTetraminos;
	std::vector<TetraminoDetailType> availableTetraminoDetails;
	TetraminoBossesInformation availableBosses;
	VictoryConditionType victoryConditionType;
	int needToPlaceDetailsCount;
	int remainTimes;
	std::vector<TetraminosForWinInformation> tetraminosCollectionForWin;
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








