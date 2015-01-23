#pragma once

#include "ServiceInterface.h"

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

private:

	TetraminisDetailsFactory *_detailsFactory;
	TetraminoDetail *_currentDetail;
	bool _currentDetailAvailable;

};

