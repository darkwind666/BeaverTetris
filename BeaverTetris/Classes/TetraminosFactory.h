#pragma once

#include "GameEnums.h"
#include "ServiceInterface.h"
#include "GameStructures.h"
#include <map>
#include "pugixml.hpp"

class Tetramino;
class KeysForEnumsDataSource;

class TetraminosFactory : public ServiceInterface
{
public:
	TetraminosFactory(KeysForEnumsDataSource *aKeysForEnumsDataSource);
	~TetraminosFactory(void);

	Tetramino* getNewTetraminoWithType(TetraminoType aType);
	int getAwardForFullTetraminosLine();
	int getAwardForElementInTetraminosChain();

private:

	std::map<TetraminoType, TetraminoInformation> _tetraminosData;
	KeysForEnumsDataSource *_keysForEnumsDataSource;
	int _awardForFullTetraminosLine;
	int _awardForElementInTetraminosChain;

	std::map<TetraminoType, TetraminoInformation> getTetraminosData();
	TetraminoInformation getTetraminoDataFromNode(pugi::xml_node &aNode);
	TetraminoType getTetraminoTypeFromNode(pugi::xml_node &aNode);
	void setAwardForTetraminosCobinations();

};

