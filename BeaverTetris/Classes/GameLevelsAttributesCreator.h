#pragma once

#include <vector>
#include "GameStructures.h"
#include "pugixml.hpp"
#include "GameEnums.h"
#include <functional>
#include <map>

class KeysForEnumsDataSource;

class GameLevelsAttributesCreator
{
public:
	GameLevelsAttributesCreator(void);
	~GameLevelsAttributesCreator(void);

	void fillEventAttributesFromeNode(GameEventInformation &aEvent, pugi::xml_node &aNode);
	void fillWinAttributesFromeNode(GameLevelInformation &aLevelData, pugi::xml_node &aNode);

private:

	KeysForEnumsDataSource *_keysForEnumsDataSource;
	std::map< VictoryConditionType, std::function<void(GameLevelInformation&, pugi::xml_node&)> > _victoryDataFactories;
	std::map< GameEventType, std::function<void(GameEventInformation&, pugi::xml_node&)> > _eventsFactories;
	
	std::map< VictoryConditionType, std::function<void(GameLevelInformation&, pugi::xml_node&)> > getVictoryDataFactories();
	std::vector<TetraminosForWinInformation> getTetraminosForWinFromNode(pugi::xml_node &node);
	TetraminoBossesInformation getBossDataForWinFromNode(pugi::xml_node &node);
	
	std::map< GameEventType, std::function<void(GameEventInformation&, pugi::xml_node&)> > getEventsFactories();

};

