#pragma once

#include "ServiceInterface.h"
#include "GameStructures.h"

class TetraminoDetail;
class TetraminisDetailsFactory;

class CurrentDetailDataSource : public ServiceInterface
{
public:
	CurrentDetailDataSource(void);
	~CurrentDetailDataSource(void);

	TetraminoDetail* getCurrentDetail();

	void makeNewDetail();
	void removeCurrentDetail();
	bool currentDetailAvailable();

	GamePositionOnBoard getCurrentDetailPosition();

private:

	TetraminisDetailsFactory *_detailsFactory;
	TetraminoDetail *_currentDetail;
	bool _currentDetailAvailable;

	TetraminoDetail* makeNewTetraminoDetail();

};

