#pragma once

#include "BossInterface.h"
#include "TetraminoObserverInterface.h"
#include "GameStructures.h"
#include <vector>

class Tetramino;
class AIMovementStrategy;
class GameBoard;

class PrincessBoss : public BossInterface, public TetraminoObserverInterface
{
public:
	PrincessBoss(GameLevelInformation aLevelInformation);
	~PrincessBoss(void);

	virtual int getVictoryStateInformationCount(void);
	virtual int getVictoryStateInformationForIndex(int aIndex);
	virtual std::string getVictoryStateIconImageForIndex(int aIndex);
	
	virtual bool playerWin(void);
	virtual void update(void);

	virtual void tetraminoRemoving(Tetramino *aTetramino);

private:

	std::vector<PrincessBossInformation> _princessBosses;
	std::string _bossKey;
	GameBoard *_gameBoard;

	std::vector<PrincessBossInformation> makePrincessWithLevelData(GameLevelInformation aLevelInformation);
	Tetramino* makeBossTetraminoWithIndexAndBossCount(int aBossIndex, int aBossCount);
	AIMovementStrategy* makeBossMovementWithTetramino(Tetramino *aTetramino);

	int getTetraminoIndex(Tetramino *aTetramino);
};

