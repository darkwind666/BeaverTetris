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
	std::vector <  std::vector< std::vector<int> >  > detailForms;
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

class AIMovementStrategy;
class Tetramino;
struct PrincessBossInformation
{
	Tetramino *bossTetramino;
	AIMovementStrategy *bossMovementStrategy;
};

class SpellInterface;
struct SpellInformation
{
	SpellInterface *spell;
	int spellCost;
};

struct TetraminoInformation
{
	int tetraminoLivesCount;
	int tetraminoCost;
};

struct PlayerInformation
{
	std::string playerName;
	int playerScore;
	int playerCompletedLevelsCount;
	int playerAvailableSpellsCount;
};

struct DatabaseInformation
{
	std::string playerName;
	int playerScore;
};

struct VictoryConditionInformation
{
	int detailsCount;
	int time;
	std::map <TetraminoType, int> gameTetraminos;
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

struct GameEventInformation
{
	GameEventType eventType;
	int eventInterval;
	int eventDuration;
	int detailsCount;
};

struct GameLevelInformation
{
	std::string levelName;
	int levelAward;
	std::vector<TetraminoType> availableTetraminos;
	std::vector<GameEventInformation> availableEvents;
	std::vector<TetraminoDetailType> availableTetraminoDetails;
	TetraminoBossesInformation availableBosses;
	VictoryConditionType victoryConditionType;
	int needToPlaceDetailsCount;
	int remainTimes;
	std::vector<TetraminosForWinInformation> tetraminosCollectionForWin;
	SpellType addSpell;

};










