#pragma once

#include "BossInterface.h"
#include "TetraminoObserverInterface.h"

class Tetramino;
class BossWithOneTetraminoDelegate;
class AIMovementStrategy;

class KingBoss : public BossInterface, public TetraminoObserverInterface
{
public:
	KingBoss(void);
	~KingBoss(void);

	virtual int getVictoryStateInformationCount(void);
	virtual int getVictoryStateInformationForIndex(int aIndex);
	virtual std::string getVictoryStateIconImageForIndex(int aIndex);
	
	virtual bool playerWin(void);
	virtual void update(void);
	
	virtual void tetraminoRemoving(Tetramino *aTetramino);

private:

	BossWithOneTetraminoDelegate *_bossWithOneTetraminoDelegate;
	AIMovementStrategy *_movementStrategy;

};

