#pragma once

#include "GameEventInterface.h"

class TetraminosFallEvent :public GameEventInterface
{
public:
	TetraminosFallEvent(void);
	~TetraminosFallEvent(void);

	bool eventTime(void);
	void runEvent(void);
	void updateEvent(void);

};

