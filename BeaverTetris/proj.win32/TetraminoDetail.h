#pragma once

#include "Tetramino.h"
#include "GameStructures.h"
#include "GameBoard.h"

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

	void rotateDetail();


private:

	GameBoard *_gameBoardTetraminos;
	int _detailWidth;
	int _detailHeight;
	GamePositionOnBoard _position;

};

