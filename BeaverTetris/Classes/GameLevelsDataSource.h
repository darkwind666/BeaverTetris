#pragma once

#include "ServiceInterface.h"
#include <string>
#include "GameStructures.h"
#include <vector>
#include "pugixml.hpp"
#include "GameEnums.h"
#include <functional>
#include <map>

class KeysForEnumsDataSource;

class GameLevelsDataSource : public ServiceInterface
{
public:
	GameLevelsDataSource(void);
	~GameLevelsDataSource(void);

	int getLevelsCount();
	std::string getLevelNameForIndex(int aIndex);
	GameLevelInformation getLevelDataForIndex(int aIndex);

private:

	std::vector<GameLevelInformation> _levelsInformation;
	KeysForEnumsDataSource *_keysForEnumsDataSource;
	std::map< VictoryConditionType, std::function<void(GameLevelInformation&, pugi::xml_node&)> > _victoryDataFactories;

	std::map< VictoryConditionType, std::function<void(GameLevelInformation&, pugi::xml_node&)> > getVictoryDataFactories();
	std::vector<TetraminosForWinInformation> getTetraminosForWinFromNode(pugi::xml_node &node);
	TetraminoBossesInformation getBossDataForWinFromNode(pugi::xml_node &node);

	std::vector<GameLevelInformation> getLevelsInformation();
	void fillLevelsInformation(std::vector<GameLevelInformation> &aLevelsInformation);
	GameLevelInformation  getLevelFromNode(pugi::xml_node &node);
	GameLevelInformation getDefaultLevel();
	SpellType getSpellFromNode(pugi::xml_node &node);
	std::vector<TetraminoType> getAvailableTetraminosFromNode(pugi::xml_node &node);
	std::vector<TetraminoDetailType> getAvailableDetails();
	std::vector<GameEventInformation> getAvailableEventsFromeNode(pugi::xml_node &node);
	void setWinConditionToLevelFromNode(GameLevelInformation &aLevelInfornation, pugi::xml_node &node);
	

};

