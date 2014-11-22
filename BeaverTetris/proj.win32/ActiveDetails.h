#pragma once

#include "GameStructures.h"

class ActiveDetails
{
public:
	ActiveDetails(void);
	~ActiveDetails(void);

	void addDetail(TetraminoDetail aDetail);
	void removeDetail(TetraminoDetail aDetail);

};

