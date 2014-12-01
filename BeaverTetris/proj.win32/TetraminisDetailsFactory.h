#pragma once

#include <map>
#include "TetraminoDetail.h"
#include "CurrentLevelDataSource.h"
#include "GameEnums.h"

class TetraminisDetailsFactory
{
public:
	TetraminisDetailsFactory(CurrentLevelDataSource *aCurrentLevelDataSource);
	~TetraminisDetailsFactory(void);

	TetraminoDetail* getNewDetail();

private:

	CurrentLevelDataSource *_currentLevelDataSource;
	std::map<TetraminoDetailType, TetraminoDetailInformation> _detailsTypesData;

	std::map<TetraminoDetailType, TetraminoDetailInformation> makeDetailsData();
	void copyMasiveToMassive(int *aSourceMassive, int *aDestinationMassive);

	TetraminoType getRandomTetraminoType();
	TetraminoDetailType getRandomTetraminoDetailType();

	TetraminoDetail* getNewDetailWithDetailTypeAndTetraminoType(TetraminoDetailType aTetraminoDetailType, TetraminoType aTetraminoType);

};

