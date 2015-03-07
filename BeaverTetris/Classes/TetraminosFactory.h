#pragma once

#include "GameEnums.h"
#include "ServiceInterface.h"
#include "GameStructures.h"
#include <map>

class Tetramino;

class TetraminosFactory : public ServiceInterface
{
public:
	TetraminosFactory(void);
	~TetraminosFactory(void);

	Tetramino* getNewTetraminoWithType(TetraminoType aType);

private:

	std::map<TetraminoType, TetraminoInformation> getTetraminosData();

	std::map<TetraminoType, TetraminoInformation> _tetraminosData;

};

