#pragma once

#include <string>

class BossInterface
{
public:
	BossInterface(void);
	virtual ~BossInterface(void);

	virtual int getVictoryStateInformationCount(void) = 0;
	virtual int getVictoryStateInformationForIndex(int aIndex) = 0;
	virtual std::string getVictoryStateIconImageForIndex(int aIndex) = 0;
	
	virtual bool playerWin(void) = 0;
	virtual void update(void) = 0;

};

