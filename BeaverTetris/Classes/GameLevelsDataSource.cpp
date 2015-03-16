#include "GameLevelsDataSource.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "KeysForEnumsDataSource.h"

using namespace std;
using namespace pugi;

const string gameLevelsFileKey = string("GameLevels.xml");
const string levelsKey = string("levels");
const string levelNameKey = string("levelName");
const string levelAwardKey = string("levelAward");
const string levelSpellKey = string("spellType");
const string levelTetraminosTypesKey = string("tetraminosTypes");
const string levelWinConditionKey = string("winCondition");
const string levelWinConditionTypeKey = string("winType");
const string levelWinDetailsCountKey = string("detailsCount");
const string levelWinTimeCountKey = string("timeCount");
const string levelWinTetraminosKey = string("tetraminos");
const string levelWinTetraminosCountKey = string("count");
const string levelWinTetraminosTypeKey = string("type");
const string levelWinBossKey = string("boss");
const string levelWinBossTypeKey = string("type");
const string levelWinBossCountKey = string("count");
const string levelGameEventsKey = string("gameEvents");
const string levelGameEventIntervalKey = string("eventInterval");

GameLevelsDataSource::GameLevelsDataSource(void)
{
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	_victoryDataFactories = getVictoryDataFactories();
	_levelsInformation = getLevelsInformation();
}


GameLevelsDataSource::~GameLevelsDataSource(void)
{
}

map< VictoryConditionType, function<void(GameLevelInformation&, xml_node&)> > GameLevelsDataSource::getVictoryDataFactories()
{
	map< VictoryConditionType, function<void(GameLevelInformation&, xml_node&)> > victoryDataFactories;

	victoryDataFactories[kPlaceSomeDetailsCondition] = [](GameLevelInformation &level, xml_node &node) {
		xml_text detailsCountText = node.child(levelWinDetailsCountKey.c_str()).text();
		int detailsCount = detailsCountText.as_int();
		level.needToPlaceDetailsCount = detailsCount;
	};

	victoryDataFactories[kRemainSomeTimeCondition] = [](GameLevelInformation &level, xml_node &node) {
		xml_text detailsCountText = node.child(levelWinTimeCountKey.c_str()).text();
		int timeCount = detailsCountText.as_int();
		level.remainTimes = timeCount;
	};

	victoryDataFactories[kRemoveSomeTetraminosCondition] = [this](GameLevelInformation &level, xml_node &node) {
		level.tetraminosCollectionForWin = getTetraminosForWinFromNode(node);
	};

	victoryDataFactories[kWinBossCondition] = [this](GameLevelInformation &level, xml_node &node) {
		level.availableBosses = getBossDataForWinFromNode(node);
	};

	return victoryDataFactories;
}

vector<TetraminosForWinInformation> GameLevelsDataSource::getTetraminosForWinFromNode(xml_node &node)
{
	vector<TetraminosForWinInformation> tetraminosForWin;
	xml_node tetramino;
	for (tetramino = node.first_child(); tetramino; tetramino = tetramino.next_sibling())
	{
		TetraminosForWinInformation tetraminosData;
		string tetraminoTypeKey = tetramino.attribute(levelWinTetraminosTypeKey.c_str()).as_string();
		tetraminosData.tetraminoType = _keysForEnumsDataSource->getTetraminoTypeForKey(tetraminoTypeKey);
		tetraminosData.tetraminosCount = tetramino.attribute(levelWinTetraminosCountKey.c_str()).as_int();
		tetraminosForWin.push_back(tetraminosData);
	}
	return tetraminosForWin;
}

TetraminoBossesInformation GameLevelsDataSource::getBossDataForWinFromNode(xml_node &node)
{
	xml_node boss = node.child(levelWinBossKey.c_str());
	TetraminoBossesInformation bossData;
	string bossTypeKey = boss.attribute(levelWinBossTypeKey.c_str()).as_string();
	bossData.aBossType = _keysForEnumsDataSource->getTetraminoTypeForKey(bossTypeKey);
	bossData.bossesCount = boss.attribute(levelWinBossCountKey.c_str()).as_int();
	return bossData;
}

vector<GameLevelInformation> GameLevelsDataSource::getLevelsInformation()
{
	vector<GameLevelInformation> levelsInformation;
	fillLevelsInformation(levelsInformation);
	return levelsInformation;
}

void GameLevelsDataSource::fillLevelsInformation(vector<GameLevelInformation> &aLevelsInformation)
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

GameLevelInformation  GameLevelsDataSource::getLevelFromNode(xml_node &node)
{
	GameLevelInformation levelInfornation = getDefaultLevel();
	levelInfornation.levelName = node.attribute(levelNameKey.c_str()).value();
	levelInfornation.levelAward = node.attribute(levelAwardKey.c_str()).as_int();
	levelInfornation.addSpell = getSpellFromNode(node);
	levelInfornation.availableTetraminos = getAvailableTetraminosFromNode(node);
	levelInfornation.availableTetraminoDetails = getAvailableDetails();
	levelInfornation.availableEvents = getAvailableEventsFromeNode(node);
	setWinConditionToLevelFromNode(levelInfornation, node);
	return levelInfornation;
}

GameLevelInformation GameLevelsDataSource::getDefaultLevel()
{
	GameLevelInformation levelInfornation;
	levelInfornation.levelName = string();
	levelInfornation.levelAward = 0;
	levelInfornation.addSpell = kZeroSpell;
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

SpellType GameLevelsDataSource::getSpellFromNode(xml_node &node)
{
	SpellType type = kZeroSpell;
	if (node.child(levelSpellKey.c_str()))
	{
		xml_text spellText = node.child(levelSpellKey.c_str()).text();
		string spellName = spellText.as_string();
		int spellType = _keysForEnumsDataSource->getSpellTypeForKey(spellName);
		type = (SpellType)spellType;
	}
	return type;
}

vector<TetraminoType> GameLevelsDataSource::getAvailableTetraminosFromNode(xml_node &node)
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

vector<TetraminoDetailType> GameLevelsDataSource::getAvailableDetails()
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

vector<GameEventInformation> GameLevelsDataSource::getAvailableEventsFromeNode(xml_node &node)
{
	vector<GameEventInformation> availableEvents;
	xml_node events = node.child(levelGameEventsKey.c_str());
	xml_node event;
	for (event = events.first_child(); event; event = event.next_sibling())
	{
		string eventType = event.name();
		GameEventInformation eventData;
		eventData.eventType = _keysForEnumsDataSource->getEventTypeForKey(eventType);
		eventData.eventInterval = event.attribute(levelGameEventIntervalKey.c_str()).as_int();
		availableEvents.push_back(eventData);
	}
	return availableEvents;
}

void GameLevelsDataSource::setWinConditionToLevelFromNode(GameLevelInformation &aLevelInfornation, xml_node &node)
{
	xml_node winCondition = node.child(levelWinConditionKey.c_str());
	string winType = winCondition.attribute(levelWinConditionTypeKey.c_str()).as_string();
	VictoryConditionType victoryType = _keysForEnumsDataSource->getVictoryConditionTypeForKey(winType);
	aLevelInfornation.victoryConditionType = victoryType;
	function<void(GameLevelInformation&, xml_node&)> victoryDataFactory = _victoryDataFactories[victoryType];
	victoryDataFactory(aLevelInfornation, winCondition);
}

int GameLevelsDataSource::getLevelsCount()
{
	return _levelsInformation.size();
}

string GameLevelsDataSource::getLevelNameForIndex(int aIndex)
{
	GameLevelInformation levelInformation = _levelsInformation[aIndex];
	return levelInformation.levelName;
}

GameLevelInformation GameLevelsDataSource::getLevelDataForIndex(int aIndex)
{
	return _levelsInformation[aIndex];
}