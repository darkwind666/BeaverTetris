#include "TetraminosFactory.h"
#include "Tetramino.h"
#include "KeysForEnumsDataSource.h"
#include "GameBalanceDataConstants.h"

using namespace std;
using namespace pugi;

TetraminosFactory::TetraminosFactory(KeysForEnumsDataSource *aKeysForEnumsDataSource)
{
	_keysForEnumsDataSource = aKeysForEnumsDataSource;
	_tetraminosData = getTetraminosData();
	setAwardForTetraminosCobinations();
}

TetraminosFactory::~TetraminosFactory(void)
{
}

map<TetraminoType, TetraminoInformation> TetraminosFactory::getTetraminosData()
{
	map<TetraminoType, TetraminoInformation> tetraminosData;
	xml_document levelsFile;
	xml_parse_result result = levelsFile.load_file(gameTetraminosFileKey.c_str());
	if (result)
	{
		xml_node tetraminosInformation = levelsFile.child(gameTetraminosDataKey.c_str());
		xml_node tetraminos = tetraminosInformation.child(gameTetraminosKey.c_str());
		for (xml_node tetramino = tetraminos.first_child(); tetramino; tetramino = tetramino.next_sibling())
		{
			TetraminoInformation tetraminoData = getTetraminoDataFromNode(tetramino);
			TetraminoType tetraminoType = getTetraminoTypeFromNode(tetramino);
			tetraminosData[tetraminoType] = tetraminoData;
		}
	}
	return tetraminosData;
}

TetraminoInformation TetraminosFactory::getTetraminoDataFromNode(xml_node &aNode)
{
	TetraminoInformation tetraminoData;
	tetraminoData.tetraminoLivesCount = aNode.attribute(gameTetraminoLivesCountKey.c_str()).as_int();
	tetraminoData.tetraminoCost = aNode.attribute(gameTetraminoCostKey.c_str()).as_int();
	return tetraminoData;
}

TetraminoType TetraminosFactory::getTetraminoTypeFromNode(pugi::xml_node &aNode)
{
	string tetraminoTypeName = aNode.attribute(gameTetraminoTypeKey.c_str()).as_string();
	TetraminoType tetraminoType = _keysForEnumsDataSource->getTetraminoTypeForKey(tetraminoTypeName);
	return tetraminoType;
}

void TetraminosFactory::setAwardForTetraminosCobinations()
{
	xml_document levelsFile;
	xml_parse_result result = levelsFile.load_file(gameTetraminosFileKey.c_str());
	if (result)
	{
		xml_node tetraminosData = levelsFile.child(gameTetraminosDataKey.c_str());
		xml_node awardForFullTetraminosLine = tetraminosData.child(awardForFullTetraminosLineKey.c_str());
		_awardForFullTetraminosLine = awardForFullTetraminosLine.attribute(awardForCombinationKey.c_str()).as_int();
		xml_node awardForElementInTetraminosChain = tetraminosData.child(awardForElementInTetraminosChainKey.c_str());
		_awardForElementInTetraminosChain = awardForElementInTetraminosChain.attribute(awardForCombinationKey.c_str()).as_int();
	}
}

Tetramino* TetraminosFactory::getNewTetraminoWithType(TetraminoType aType)
{
	TetraminoInformation tetraminoData = _tetraminosData[aType];
	Tetramino *newTetramino = new Tetramino(aType, tetraminoData.tetraminoLivesCount, tetraminoData.tetraminoCost);
	return newTetramino;
}

int TetraminosFactory::getAwardForFullTetraminosLine()
{
	return _awardForFullTetraminosLine;
}

int TetraminosFactory::getAwardForElementInTetraminosChain()
{
	return _awardForElementInTetraminosChain;
}
