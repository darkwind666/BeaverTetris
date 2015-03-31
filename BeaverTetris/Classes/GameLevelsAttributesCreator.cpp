#include "GameLevelsAttributesCreator.h"

#include "GameBalanceDataConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "KeysForEnumsDataSource.h"
#include <string>

using namespace std;
using namespace pugi;

GameLevelsAttributesCreator::GameLevelsAttributesCreator(void)
{
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	_eventsFactories = getEventsFactories();
	_victoryDataFactories = getVictoryDataFactories();
}


GameLevelsAttributesCreator::~GameLevelsAttributesCreator(void)
{
}

map< GameEventType, function<void(GameEventInformation&, xml_node&)> > GameLevelsAttributesCreator::getEventsFactories()
{
	map< GameEventType, function<void(GameEventInformation&, xml_node&)> > eventsFactories;

	eventsFactories[kTetraminosFallEvent] = [](GameEventInformation &event, xml_node &node){
		int detailsCount = node.attribute(levelGameEventDetailsCountKey.c_str()).as_int();
		event.detailsCount = detailsCount;
	};

	eventsFactories[kTimeAccelerationEvent] = [](GameEventInformation &event, xml_node &node){
		int eventDuration = node.attribute(levelGameEventDurationKey.c_str()).as_int();
		int fallingSpeed = node.attribute(levelGameEventFallingSpeedKey.c_str()).as_int();
		event.eventDuration = eventDuration;
		event.fallingSpeed = fallingSpeed;
	};

	return eventsFactories;
}

map< VictoryConditionType, function<void(GameLevelInformation&, xml_node&)> > GameLevelsAttributesCreator::getVictoryDataFactories()
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

vector<TetraminosForWinInformation> GameLevelsAttributesCreator::getTetraminosForWinFromNode(xml_node &node)
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

TetraminoBossesInformation GameLevelsAttributesCreator::getBossDataForWinFromNode(xml_node &node)
{
	xml_node boss = node.child(levelWinBossKey.c_str());
	TetraminoBossesInformation bossData;
	string bossTypeKey = boss.attribute(levelWinBossTypeKey.c_str()).as_string();
	bossData.aBossType = _keysForEnumsDataSource->getTetraminoTypeForKey(bossTypeKey);
	bossData.bossesCount = boss.attribute(levelWinBossCountKey.c_str()).as_int();
	return bossData;
}

void GameLevelsAttributesCreator::fillEventAttributesFromeNode(GameEventInformation &aEvent, xml_node &aNode)
{
	function<void(GameEventInformation&, xml_node&)> eventFactory = _eventsFactories[aEvent.eventType];
	eventFactory(aEvent, aNode);
}

void GameLevelsAttributesCreator::fillWinAttributesFromeNode(GameLevelInformation &aLevelData, xml_node &aNode)
{
	function<void(GameLevelInformation&, xml_node&)> victoryDataFactory = _victoryDataFactories[aLevelData.victoryConditionType];
	victoryDataFactory(aLevelData, aNode);
}