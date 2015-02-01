#pragma once

class GameBoard;
class CurrentPlayerDataSource;
class AwardForTetraminoDataSource;
class Tetramino;

class FullLineCombination
{
public:
	FullLineCombination(GameBoard *aGameBoard);
	~FullLineCombination(void);

	void checkFullLineCombination();

private:

	GameBoard *_gameBoard;
	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	CurrentPlayerDataSource *_currentPlayerDataSource;

	void checkFullLineInBoardRow(int aRow);
	bool fullLineCheck(int lineIndex);
	int getPlayerAwardForLine(int aIndex);
	int getAwardForTetramino(Tetramino *aTetramino);
	void addAwardToPlayerScore(int aAward);
	void removeKilledTetraminosFromBoardOnLine(int aLine);

};

