#pragma once

#include "ServiceInterface.h"

class GameBoard;
class CurrentPlayerDataSource;
class AwardForTetraminoDataSource;
class Tetramino;
class ExplosionAnimationDelegate;

class FullLineCombination : public ServiceInterface
{
public:
	FullLineCombination(GameBoard *aGameBoard);
	~FullLineCombination(void);

	void checkFullLineCombination();
	void setDelegate(ExplosionAnimationDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	ExplosionAnimationDelegate *_delegate;

	void checkFullLineInBoardRow(int aRow);
	bool fullLineCheck(int lineIndex);

	void sendMessagesToDelegateAccordingToLine(int aLine);
	void setUpPlayerScoreWithAwardFromLine(int aLine);

	int getPlayerAwardForLine(int aIndex);
	int getAwardForTetramino(Tetramino *aTetramino);
	void addAwardToPlayerScore(int aAward);
	void reduceTetraminosLifesInLine(int aLine);
	void removeKilledTetraminosFromBoardOnLine(int aLine);

	void sendDelegateKilledTetraminosFromBoardOnLine(int aLine);
	void sendDelegatePlayerAward(int aPlayerAward);

};

