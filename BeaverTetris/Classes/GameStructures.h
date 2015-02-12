#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "cocos2d.h"
#include "GameEnums.h"

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

struct PlayerControllInformation
{
	std::string imageKey;
	std::function<void()> callback;
	int keyboardKey;
};

struct ViewElementInformation
{
	std::string elementImage;
	cocos2d::Vec2 elementPosition;
	cocos2d::Vec2 elementOffset;
	cocos2d::Vec2 elementActionFinalPosition;
	int elementZOrder;

};

struct TetraminoDetailInformation
{
	bool rotateble;
	std::vector< std::vector<int> > tetraminoElements;
};

struct NewTetraminoDetailRequest
{
	TetraminoDetailType tetraminoDetailType; 
	TetraminoType tetraminoType;
};

struct VictoryConditionViewElements
{
	cocos2d::Sprite* image; 
	cocos2d::LabelTTF* label;
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

struct SpellInformation
{
	SpellType spellType;
	std::string spellName;
	int spellCost;
};








