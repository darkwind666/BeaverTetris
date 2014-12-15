#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"
#include "TetraminisDetailsFactory.h"

class PlaceSomeDetailsCondition :public VictoryConditionInterface
{
public:
	PlaceSomeDetailsCondition(GameLevelInformation aLevelInformation);
	~PlaceSomeDetailsCondition(void);

    int getVictoryStateInformationCount(void);
    int getVictoryStateInformationForIndex(int aIndex);
    std::string getVictoryStateIconImageForIndex(int aIndex);
    
    bool playerWin(void);
    void update(void);

private:

	int _needToPlaceDetailsCount;
	int _placedDetailsCount;
	TetraminisDetailsFactory *_tetraminisDetailsFactory;

};

