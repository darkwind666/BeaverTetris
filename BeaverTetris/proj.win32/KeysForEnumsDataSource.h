#pragma once

#include "GameEnums.h"
#include <string>

class KeysForEnumsDataSource
{
public:
	KeysForEnumsDataSource(void);
	~KeysForEnumsDataSource(void);

	std::string getKeyForTetraminoType(TetraminoType aTetraminoType);

};

