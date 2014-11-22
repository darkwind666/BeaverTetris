#pragma once

class VictoryCondition;

class CurrentGameVictoryConditionDataSource
{
public:
	CurrentGameVictoryConditionDataSource(void);
	~CurrentGameVictoryConditionDataSource(void);

	VictoryCondition getCurrentVictoryCondition(void);
	void resetVictoryCondition(void);

};

