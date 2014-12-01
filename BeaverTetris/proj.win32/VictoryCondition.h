#pragma once

#include "EventHandlerInterface.h"
#include <string>

class VictoryCondition :public EventHandlerInterface
{
public:
	VictoryCondition(void);
	~VictoryCondition(void);


	virtual int getVictoryStateInformationCount(void) = 0;
	virtual std::string getVictoryStateInformationForIndex(int aIndex) = 0;
	virtual std::string getVictoryStateIconImageForIndex(int aIndex) = 0;

	virtual bool playerWin(void) = 0;

};

