#pragma once

#include "GameStructures.h"

class TetraminoDetail;

class NewGameTetraminoDataSource
{
public:
	NewGameTetraminoDataSource(void);
	~NewGameTetraminoDataSource(void);

	TetraminoDetail getNewDetail(void);

};

