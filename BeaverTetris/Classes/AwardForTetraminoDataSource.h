#pragma once

#include "ServiceInterface.h"
#include "GameEnums.h"

class AwardForTetraminoDataSource : public ServiceInterface
{
public:
	AwardForTetraminoDataSource();
	~AwardForTetraminoDataSource(void);

	int getAwardForTetraminoType(TetraminoType aTetraminoType);

};

