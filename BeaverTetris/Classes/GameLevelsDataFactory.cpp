#include "GameLevelsDataFactory.h"
#include "GameViewElementsKeys.h"
#include "GameBalanceDataConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "KeysForEnumsDataSource.h"
#include "GameLevelsAttributesCreator.h"

using namespace std;
using namespace pugi;

GameLevelsDataFactory::GameLevelsDataFactory(void)
{
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	_gameLevelsAttributesCreator = new GameLevelsAttributesCreator();
}

GameLevelsDataFactory::~GameLevelsDataFactory(void)
{
	delete _gameLevelsAttributesCreator;
}

vector<GameLevelInformation> GameLevelsDataFactory::getLevelsInformation()
{
	vector<GameLevelInformation> levelsInformation;
	fillLevelsInformation(levelsInformation);
	return levelsInformation;
}

void GameLevelsDataFactory::fillLevelsInformation(vector<GameLevelInformation> &aLevelsInformation)
{
	xml_document levelsFile;
	xml_parse_result result = levelsFile.load_file(gameLevelsFileKey.c_str());
	if (result)
	{
		xml_node levels = levelsFile.child(levelsKey.c_str());
		xml_node level;
		for (level = levels.first_child(); level; level = level.next_sibling())
		{
			GameLevelInformation levelInfornation = getLevelFromNode(level);
			aLevelsInformation.push_back(levelInfornation);
		}
	}
}

GameLevelInformation  GameLevelsDataFactory::getLevelFromNode(xml_node &node)
{
	GameLevelInformation levelInfornation = getDefaultLevel();
	levelInfornation.levelName = node.attribute(levelNameKey.c_str()).value();
	levelInfornation.levelAward = node.attribute(levelAwardKey.c_str()).as_int();
	levelInfornation.spellsData = getSpellsDataFromNode(node);
	levelInfornation.availableTetraminos = getAvailableTetraminosFromNode(node);
	levelInfornation.availableTetraminoDetails = getAvailableDetails();
	levelInfornation.availableEvents = getAvailableEventsFromeNode(node);
	setWinConditionToLevelFromNode(levelInfornation, node);
	return levelInfornation;
}

GameLevelInformation GameLevelsDataFactory::getDefaultLevel()
{
	GameLevelInformation levelInfornation;
	levelInfornation.levelName = string();
	levelInfornation.levelAward = 0;
	levelInfornation.spellsData = map<string, int>();
	levelInfornation.availableTetraminos = vector<TetraminoType>();
	levelInfornation.availableTetraminoDetails = vector<TetraminoDetailType>();
	levelInfornation.availableEvents = vector<GameEventInformation>();
	TetraminoBossesInformation defaultBoss;
	defaultBoss.aBossType = kTetraminoEmpty;
	defaultBoss.bossesCount = 0;
	levelInfornation.availableBosses = defaultBoss;
	levelInfornation.needToPlaceDetailsCount = 0;
	levelInfornation.remainTimes = 0;
	levelInfornation.tetraminosCollectionForWin = vector<TetraminosForWinInformation>();
	return levelInfornation;
}

map<string, int> GameLevelsDataFactory::getSpellsDataFromNode(xml_node &node)
{
	map<string, int> spellsData;
	if (node.child(levelSpellsKey.c_str()))
	{
		xml_node spells = node.child(levelSpellsKey.c_str());
		spellsData = getSpellsFromNode(spells);
	}
	return spellsData;
}

map<string, int> GameLevelsDataFactory::getSpellsFromNode(xml_node &node)
{
	map<string, int> spellsData;
	for (xml_node spell = node.first_child(); spell; spell = spell.next_sibling())
	{
		string spellType = spell.attribute(levelSpellTypeKey.c_str()).as_string();
		int spellCount = 0;
		if (spell.attribute(levelSpellCountKey.c_str()))
		{
			spellCount = spell.attribute(levelSpellCountKey.c_str()).as_int();
		}
		spellsData[spellType] = spellCount;
	}
	return spellsData;
}

vector<TetraminoType> GameLevelsDataFactory::getAvailableTetraminosFromNode(xml_node &node)
{
	vector<TetraminoType> availableTetraminos;
	xml_node tetraminos = node.child(levelTetraminosTypesKey.c_str());
	xml_node tetramino;
	for (tetramino = tetraminos.first_child(); tetramino; tetramino = tetramino.next_sibling())
	{
		xml_text tetraminoText = tetramino.text();
		string tetraminoType = tetraminoText.as_string();
		TetraminoType type = _keysForEnumsDataSource->getTetraminoTypeForKey(tetraminoType);
		availableTetraminos.push_back(type);
	}
	return availableTetraminos;
}

vector<TetraminoDetailType> GameLevelsDataFactory::getAvailableDetails()
{
	vector<TetraminoDetailType> availableTetraminoDetails;
	
	availableTetraminoDetails.push_back(kTetraminoDetail1);
	availableTetraminoDetails.push_back(kTetraminoDetail2);
	availableTetraminoDetails.push_back(kTetraminoDetail3);
	availableTetraminoDetails.push_back(kTetraminoDetail4);
	availableTetraminoDetails.push_back(kTetraminoDetail5);
	availableTetraminoDetails.push_back(kTetraminoDetail6);
	availableTetraminoDetails.push_back(kTetraminoDetail7);
	availableTetraminoDetails.push_back(kTetraminoDetail8);
	
	return availableTetraminoDetails;
}

vector<GameEventInformation> GameLevelsDataFactory::getAvailableEventsFromeNode(xml_node &node)
{
	vector<GameEventInformation> availableEvents;
	xml_node events = node.child(levelGameEventsKey.c_str());
	xml_node event;
	for (event = events.first_child(); event; event = event.next_sibling())
	{
		string eventType = event.name();
		GameEventType type = _keysForEnumsDataSource->getEventTypeForKey(eventType);
		GameEventInformation eventData;
		eventData.eventType = type;
		eventData.eventInterval = event.attribute(levelGameEventIntervalKey.c_str()).as_int();
		_gameLevelsAttributesCreator->fillEventAttributesFromeNode(eventData, event);
		availableEvents.push_back(eventData);
	}
	return availableEvents;
}

void GameLevelsDataFactory::setWinConditionToLevelFromNode(GameLevelInformation &aLevelInfornation, xml_node &node)
{
	xml_node winCondition = node.child(levelWinConditionKey.c_str());
	string winType = winCondition.attribute(levelWinConditionTypeKey.c_str()).as_string();
	VictoryConditionType victoryType = _keysForEnumsDataSource->getVictoryConditionTypeForKey(winType);
	aLevelInfornation.victoryConditionType = victoryType;
	_gameLevelsAttributesCreator->fillWinAttributesFromeNode(aLevelInfornation, winCondition);
}