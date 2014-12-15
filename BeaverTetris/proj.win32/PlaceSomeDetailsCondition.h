#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class PlaceSomeDetailsCondition :public VictoryConditionInterface
{
public:
	PlaceSomeDetailsCondition(LevelInformation aLevelInformation);
	~PlaceSomeDetailsCondition(void);

    int getVictoryStateInformationCount(void);
    std::string getVictoryStateInformationForIndex(int aIndex);
    std::string getVictoryStateIconImageForIndex(int aIndex);
    
    bool playerWin(void);
    void update(void);

};

