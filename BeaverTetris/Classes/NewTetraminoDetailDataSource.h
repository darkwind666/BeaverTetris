#pragma once

#include "ServiceInterface.h"
#include "GameEnums.h"
#include "GameStructures.h"
#include <map>

class CurrentLevelDataSource;
class TetraminoDetail;
class Tetramino;
class TetraminosFactory;

class NewTetraminoDetailDataSource : public ServiceInterface
{
public:
	NewTetraminoDetailDataSource(void);
	~NewTetraminoDetailDataSource(void);

	TetraminoDetail* getNewDetail();
	int getCreatedDetailsCount();

private:

	CurrentLevelDataSource *_currentLevelDataSource;
	std::map<TetraminoDetailType, TetraminoDetailInformation> _detailsTypesData;
	int _createdDetailsCount;
	TetraminosFactory *_tetraminosFactory;

	NewTetraminoDetailRequest getTetraminoDetailRequest();
	TetraminoType getRandomTetraminoType();
	TetraminoDetailType getRandomTetraminoDetailType();
	
	TetraminoDetail* getNewDetailWithRequest(NewTetraminoDetailRequest aRequest);
	void setInDetailTetraminosWithRequest(TetraminoDetail* aDetail, NewTetraminoDetailRequest aRequest);
	void setInDetailTetraminosLineWithRequest(TetraminoDetail* aDetail, int aLineIndex, NewTetraminoDetailRequest aRequest);
	Tetramino* getTetraminoWithFlagAndType(int aTetraminoFlag, TetraminoType aTetraminoType);
	void setDetailStartPosition(TetraminoDetail* aDetail);
	void setDetailRotatebleFlagWithDetailType(TetraminoDetail* aDetail, TetraminoDetailType aTetraminoDetailType);

};

