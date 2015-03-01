#pragma once

#include "TetraminoRemovingObserverInterface.h"
#include "VictoryConditionInterface.h"
#include "GameStructures.h"
#include <vector>

class KeysForEnumsDataSource;

class RemoveSomeTetraminosCondition :public VictoryConditionInterface, public TetraminoRemovingObserverInterface
{
public:
	RemoveSomeTetraminosCondition(GameLevelInformation aLevelInformation);
	~RemoveSomeTetraminosCondition(void);

	virtual int getVictoryStateInformationCount(void);
	virtual int getVictoryStateInformationForIndex(int aIndex);
	virtual std::string getVictoryStateIconImageForIndex(int aIndex);
	
	virtual bool playerWin(void);
	virtual void update(void);
	virtual void tetraminoRemoving(Tetramino *aTetramino);

private:

	std::vector<TetraminosForWinInformation> _tetraminosCollectionForWin;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

	void removeFilledCollections();
	std::vector<int> getIndexesToRemove();
	void removeCollectionsForIndexes(std::vector<int> aIndexes);

};

