#include "KeysForEnumsDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;

KeysForEnumsDataSource::KeysForEnumsDataSource(void)
{
	_tetraminoKeys = makeTetraminoKeys();
	_spellsKeys = makeSpellsKeys();
	_victoryConditionKeys = makeVictoryConditionKeys();
	_gameEventsKeys = makeGameEventsKeys();
}


KeysForEnumsDataSource::~KeysForEnumsDataSource(void)
{
}

map<TetraminoType, string> KeysForEnumsDataSource::makeTetraminoKeys()
{
	
	map<TetraminoType, string> tetraminoKeys;

	tetraminoKeys[kTetraminoRed] = redTetraminoKey;
	tetraminoKeys[kTetraminoGreen] = greenTetraminoKey;
	tetraminoKeys[kTetraminoBlue] = blueTetraminoKey;
	tetraminoKeys[kTetraminoGold] = goldTetraminoKey;
	tetraminoKeys[kTetraminoBlack] = blackTetraminoKey;
	tetraminoKeys[kTetraminoBossQueen] = queenTetraminoKey;
	tetraminoKeys[kTetraminoBossPrincess] = princessTetraminoKey;
	tetraminoKeys[kTetraminoBossKing] = kingTetraminoKey;

	return tetraminoKeys;
}

map<string, SpellType> KeysForEnumsDataSource::makeSpellsKeys()
{
	map<string, SpellType> spellsKeys;

	spellsKeys[removeCurrentDetailSpellKey] = kRocketSpell;
	spellsKeys[firestormSpellKey] = kFirestormSpell;
	spellsKeys[removeRandomTetraminosSpellKey] = kRandomExplosionsSpell;
	spellsKeys[cohesionSpellKey] = kCohessionSpell;

	return spellsKeys;
}

map<string, VictoryConditionType> KeysForEnumsDataSource::makeVictoryConditionKeys()
{
	map<string, VictoryConditionType> victoryConditionKeys;

	victoryConditionKeys[placeDetailsIconKey] = kPlaceSomeDetailsCondition;
	victoryConditionKeys[remainSomeTimeIconKey] = kRemainSomeTimeCondition;
	victoryConditionKeys[removeSomeTetraminosKey] = kRemoveSomeTetraminosCondition;
	victoryConditionKeys[killBossKey] = kWinBossCondition;

	return victoryConditionKeys;
}

map<string, GameEventType> KeysForEnumsDataSource::makeGameEventsKeys()
{
	map<string, GameEventType> gameEventsKeys;

	gameEventsKeys[accelerateEventKey] = kTimeAccelerationEvent;
	gameEventsKeys[fallDetailsEventKey] = kTetraminosFallEvent;

	return gameEventsKeys;
}

string KeysForEnumsDataSource::getKeyForTetraminoType(TetraminoType aTetraminoType)
{
	return _tetraminoKeys[aTetraminoType];
}

TetraminoType KeysForEnumsDataSource::getTetraminoTypeForKey(string aKey)
{
	TetraminoType type = kTetraminoEmpty;
	map<TetraminoType, string>::iterator tetraminosIterator;
	for (tetraminosIterator = _tetraminoKeys.begin(); tetraminosIterator != _tetraminoKeys.end(); tetraminosIterator++)
	{
		string key = tetraminosIterator->second;
		if (aKey == key)
		{
			type = tetraminosIterator->first;
			break;
		}
	}
	return type;
}

SpellType KeysForEnumsDataSource::getSpellTypeForKey(string aKey)
{
	return _spellsKeys[aKey];
}

string KeysForEnumsDataSource::getKeyForSpellType(SpellType aSpellType)
{
	string spellKey = string();
	map<string, SpellType>::iterator spellsIterator;
	for (spellsIterator = _spellsKeys.begin(); spellsIterator != _spellsKeys.end(); spellsIterator++)
	{
		SpellType spellType = spellsIterator->second;
		if (spellType == aSpellType)
		{
			spellKey = spellsIterator->first;
			break;
		}
	}
	return spellKey;
}

VictoryConditionType KeysForEnumsDataSource::getVictoryConditionTypeForKey(string aKey)
{
	return _victoryConditionKeys[aKey];
}

GameEventType KeysForEnumsDataSource::getEventTypeForKey(string aKey)
{
	return _gameEventsKeys[aKey];
}