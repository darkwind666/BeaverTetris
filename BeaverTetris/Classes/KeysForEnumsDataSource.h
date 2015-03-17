#pragma once

#include "ServiceInterface.h"
#include "GameEnums.h"
#include <string>
#include <map>

class KeysForEnumsDataSource : public ServiceInterface
{
public:
	KeysForEnumsDataSource(void);
	~KeysForEnumsDataSource(void);

	std::string getKeyForTetraminoType(TetraminoType aTetraminoType);
	SpellType getSpellTypeForKey(std::string aKey);
	std::string getKeyForSpellType(SpellType aSpellType);
	TetraminoType getTetraminoTypeForKey(std::string aKey);
	VictoryConditionType getVictoryConditionTypeForKey(std::string aKey);
	GameEventType getEventTypeForKey(std::string aKey);

private:

	std::map<TetraminoType, std::string> _tetraminoKeys;
	std::map<std::string, SpellType> _spellsKeys;
	std::map<std::string, VictoryConditionType> _victoryConditionKeys;
	std::map<std::string, GameEventType> _gameEventsKeys;

	std::map<TetraminoType, std::string> makeTetraminoKeys();
	std::map<std::string, SpellType> makeSpellsKeys();
	std::map<std::string, VictoryConditionType> makeVictoryConditionKeys();
	std::map<std::string, GameEventType> makeGameEventsKeys();

};

