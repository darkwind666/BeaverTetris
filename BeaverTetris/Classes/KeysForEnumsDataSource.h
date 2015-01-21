#pragma once

#include "ServiceInterface.h"
#include "GameEnums.h"
#include <string>

class KeysForEnumsDataSource : public ServiceInterface
{
public:
	KeysForEnumsDataSource(void);
	~KeysForEnumsDataSource(void);

	std::string getKeyForTetraminoType(TetraminoType aTetraminoType);

};

