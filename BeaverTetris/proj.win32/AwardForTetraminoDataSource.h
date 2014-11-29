#pragma once

#include "GameEnums.h"
#include "TetraminosCharacteristicsDataSource.h"

class AwardForTetraminoDataSource
{
public:
	AwardForTetraminoDataSource(TetraminosCharacteristicsDataSource *aTetraminosCharacteristicsDataSource);
	~AwardForTetraminoDataSource(void);

	int getAwardForTetraminoType(TetraminoType aTetraminoType);

};

