#pragma once

#include "Tetramino.h"
#include <vector>
#include "GameStructures.h"

class TetraminosPositionsDelegate
{
public:
	TetraminosPositionsDelegate(Tetramino **tetramins, int boardHeight, int boardWidth);
	~TetraminosPositionsDelegate(void);

	GamePositionOnBoard getTetraminoPosition(Tetramino *aTetramino);
	Tetramino* getTetraminoForXYposition(int xPosition, int yPosition);
	std::vector <GamePositionOnBoard> getAvailableTetraminis();
	std::vector <GamePositionOnBoard> getTetraminisForType(TetraminoType aTetraminoType);

private:

	typedef bool (TetraminosPositionsDelegate::*predicateFunction)(TetraminoType aFirstType, TetraminoType aSecondType);

	Tetramino **_tetramins;
	int _gameBoardHeight;
	int _gameBoardWidth;

	std::vector <GamePositionOnBoard> findAllTetraminisForTypeAndPredicate(TetraminoType aTetraminoType, predicateFunction aPredicateFunction);
	bool equalType(TetraminoType aFirstType, TetraminoType aSecondType);
	bool largerType(TetraminoType aFirstType, TetraminoType aSecondType);

};

