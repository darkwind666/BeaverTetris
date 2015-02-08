#pragma once

class Tetramino;
class GameBoard;
class TetraminoDetail;

class TetraminoDetailLocatorDelegate
{
public:
	TetraminoDetailLocatorDelegate(GameBoard *aGameBoard);
	~TetraminoDetailLocatorDelegate(void);

	void writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail);

private:

	GameBoard *_gameBoard;

	void writeTetraminoRowFromDetail(int aRow, TetraminoDetail *aTetraminoDetail);
	bool checkTetraminoForPlacingInBoardRow(Tetramino *aTetramino, int aRow, TetraminoDetail *aTetraminoDetail);

};

