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

private:

	std::map<TetraminoType, std::string> _tetraminoKeys;

	std::map<TetraminoType, std::string> makeTetraminoKeys();

};

