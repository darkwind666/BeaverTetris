#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class NewTetraminoDetailDataSource;

class PlaceSomeDetailsCondition :public VictoryConditionInterface
{
public:
	PlaceSomeDetailsCondition(GameLevelInformation aLevelInformation);
	~PlaceSomeDetailsCondition(void);

    virtual int getVictoryStateInformationCount(void);
    virtual int getVictoryStateInformationForIndex(int aIndex);
    virtual std::string getVictoryStateIconImageForIndex(int aIndex);
    
    virtual bool playerWin(void);
    virtual void update(void);

private:

	int _needToPlaceDetailsCount;
	int _placedDetailsCount;
	NewTetraminoDetailDataSource *_newTetraminoDetailDataSource;

};

