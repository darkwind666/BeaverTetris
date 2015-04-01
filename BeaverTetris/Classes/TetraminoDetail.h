#pragma once

#include "GameStructures.h"
#include "GameEnums.h"
#include <vector>

class GameBoard;
class Tetramino;

class TetraminoDetail
{
public:
	TetraminoDetail(int width, int height);
	TetraminoDetail(TetraminoDetail &copy);
	~TetraminoDetail(void);

	int getDetailWidth();
	int getDetailHeight();

	Tetramino* getTetraminoForXY(int xPosition, int yPosition);
	GamePositionOnBoard getDetailPosition();
	GamePositionOnBoard getPositionForIndex(int aIndex);
	int getIndexForPosition(GamePositionOnBoard aPosition);
	std::vector<GamePositionOnBoard> getAvailableTetraminos();

	void setTetraminoForXY(Tetramino *aTetramino, int xPosition, int yPosition);
	void setDetailPosition(GamePositionOnBoard aDetailPosition);
	void setDetailRotatebleFlag(bool aRotatable);
	void setDetailTetraminosType(TetraminoType aType);
	void setDetailForms(std::vector <  std::vector< std::vector<int> >  > aDetailForms);
	
	void rotateDetail();
	GamePositionOnBoard convertPositionInDetailToAbsolutePosition(GamePositionOnBoard aPosition);
	GamePositionOnBoard convertAbsolutePositionToPositionInDetail(GamePositionOnBoard aPosition);
	bool absolutePositionInDetail(GamePositionOnBoard aPosition);

private:

	GameBoard *_gameBoardTetraminos;
	int _detailWidth;
	int _detailHeight;
	bool _rotatable;
	GamePositionOnBoard _position;
	TetraminoType _tetraminosType;
	std::vector <  std::vector< std::vector<int> >  > _detailForms;
	int _currentDetailFormIndex;

	void copyTetraminosInDetail(TetraminoDetail *aDestinationDetail);
	void rotateDetailBoard();
	void rotateDetailAccordingToFormIndex();
	std::vector<Tetramino*> getTetraminosForType(TetraminoType aType);
	void fillTetraminosWithFlag(std::vector<Tetramino*> &emptyTetraminos, int aFlag);
	void fillTetraminosLineFromTetraminosWithFlag(int aLine, std::vector<Tetramino*> &emptyTetraminos, int aFlag);

};

