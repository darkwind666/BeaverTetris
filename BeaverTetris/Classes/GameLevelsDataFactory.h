#pragma once

#include <vector>
#include "GameStructures.h"
#include "pugixml.hpp"
#include "GameEnums.h"
#include <functional>
#include <map>

class KeysForEnumsDataSource;

class GameLevelsDataFactory
{
public:
	GameLevelsDataFactory(void);
	~GameLevelsDataFactory(void);

	std::vector<GameLevelInformation> getLevelsInformation();

private:

	KeysForEnumsDataSource *_keysForEnumsDataSource;
	std::map< VictoryConditionType, std::function<void(GameLevelInformation&, pugi::xml_node&)> > _victoryDataFactories;

	std::map< VictoryConditionType, std::function<void(GameLevelInformation&, pugi::xml_node&)> > getVictoryDataFactories();
	std::vector<TetraminosForWinInformation> getTetraminosForWinFromNode(pugi::xml_node &node);
	TetraminoBossesInformation getBossDataForWinFromNode(pugi::xml_node &node);

	void fillLevelsInformation(std::vector<GameLevelInformation> &aLevelsInformation);
	GameLevelInformation  getLevelFromNode(pugi::xml_node &node);
	GameLevelInformation getDefaultLevel();
	SpellType getSpellFromNode(pugi::xml_node &node);
	std::vector<TetraminoType> getAvailableTetraminosFromNode(pugi::xml_node &node);
	std::vector<TetraminoDetailType> getAvailableDetails();
	std::vector<GameEventInformation> getAvailableEventsFromeNode(pugi::xml_node &node);
	void setWinConditionToLevelFromNode(GameLevelInformation &aLevelInfornation, pugi::xml_node &node);

};

