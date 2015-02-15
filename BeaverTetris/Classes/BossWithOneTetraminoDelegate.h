#pragma once

#include <string>

class Tetramino;

class BossWithOneTetraminoDelegate
{
public:
	BossWithOneTetraminoDelegate(Tetramino *aTetramino);
	~BossWithOneTetraminoDelegate(void);

	int getVictoryStateInformationCount(void);
	int getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	bool playerWin(void);
	void tetraminoRemoving();

private:

	Tetramino *_bossTetramino;
	bool _bossKilled;
	std::string _bossKey;

	int getBossStateInformation();
	bool getBossWin();

};

