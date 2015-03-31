#pragma once

#include <vector>
#include <map>
#include <string>
#include "GameStructures.h"
#include "pugixml.hpp"
#include "GameEnums.h"

class KeysForEnumsDataSource;
class GameLevelsAttributesCreator;

class GameLevelsDataFactory
{
public:
	GameLevelsDataFactory(void);
	~GameLevelsDataFactory(void);

	std::vector<GameLevelInformation> getLevelsInformation();

private:

	KeysForEnumsDataSource *_keysForEnumsDataSource;
	GameLevelsAttributesCreator *_gameLevelsAttributesCreator;
	
	void fillLevelsInformation(std::vector<GameLevelInformation> &aLevelsInformation);
	GameLevelInformation  getLevelFromNode(pugi::xml_node &node);
	GameLevelInformation getDefaultLevel();
	std::map<std::string, int> getSpellsDataFromNode(pugi::xml_node &node);
	std::map<std::string, int> getSpellsFromNode(pugi::xml_node &node);
	std::vector<TetraminoType> getAvailableTetraminosFromNode(pugi::xml_node &node);
	std::vector<TetraminoDetailType> getAvailableDetails();
	std::vector<GameEventInformation> getAvailableEventsFromeNode(pugi::xml_node &node);
	void setWinConditionToLevelFromNode(GameLevelInformation &aLevelInfornation, pugi::xml_node &node);

};

