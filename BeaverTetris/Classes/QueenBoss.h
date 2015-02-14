#pragma once

#include "BossInterface.h"
#include "TetraminoObserverInterface.h"

class Tetramino;

class QueenBoss : public BossInterface, public TetraminoObserverInterface
{
public:
	QueenBoss(void);
	~QueenBoss(void);

	virtual int getVictoryStateInformationCount(void);
	virtual int getVictoryStateInformationForIndex(int aIndex);
	virtual std::string getVictoryStateIconImageForIndex(int aIndex);
	
	virtual bool playerWin(void);
	virtual void update(void);

	virtual void tetraminoRemoving(Tetramino *aTetramino);

private:

	Tetramino *_bossTetramino;
	bool _bossKilled;
	std::string _bossKey;

	int getBossStateInformation();
	bool getBossWin();

};

