#pragma once

#include "ServiceInterface.h"
#include "GameStructures.h"

class TetraminoDetail;
class NewTetraminoDetailDataSource;

class CurrentDetailDataSource : public ServiceInterface
{
public:
	CurrentDetailDataSource(void);
	~CurrentDetailDataSource(void);

	TetraminoDetail* getCurrentDetail();

	void removeCurrentDetail();
	bool currentDetailAvailable();
	void makeNewDetail(void);

	GamePositionOnBoard getCurrentDetailPosition();

private:

	NewTetraminoDetailDataSource *_newTetraminoDetailDataSource;
	TetraminoDetail *_currentDetail;
	bool _currentDetailAvailable;

};

