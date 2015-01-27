#pragma once

#include "GameStructures.h"

class GameBoard;
class Tetramino;

class TetraminoDetail
{
public:
	TetraminoDetail(int width, int height);
	~TetraminoDetail(void);

	int getDetailWidth();
	int getDetailHeight();

	Tetramino* getTetraminoForXY(int xPosition, int yPosition);
	GamePositionOnBoard getDetailPosition();
	std::vector<GamePositionOnBoard> getAvailableTetraminos();

	void setTetraminoForXY(Tetramino *aTetramino, int xPosition, int yPosition);
	void setDetailPosition(GamePositionOnBoard aDetailPosition);
	void setDetailRotatebleFlag(bool aRotatable);

	void rotateDetail();
	void rotateDetailBoard();
	void rotateColumnAndPlaceInNewBoard(int aColumn, GameBoard *aGameBoard);
	GamePositionOnBoard convertPositionInDetailToAbsolutePosition(GamePositionOnBoard aPosition);
	GamePositionOnBoard convertAbsolutePositionToPositionInDetail(GamePositionOnBoard aPosition);

private:

	GameBoard *_gameBoardTetraminos;
	int _detailWidth;
	int _detailHeight;
	bool _rotatable;
	GamePositionOnBoard _position;

};

