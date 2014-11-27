#pragma once

#include "TetraminoDetail.h"

class TetraminisDetailsFactory
{
public:
	TetraminisDetailsFactory(void);
	~TetraminisDetailsFactory(void);

	TetraminoDetail* getNewDetail();

};

