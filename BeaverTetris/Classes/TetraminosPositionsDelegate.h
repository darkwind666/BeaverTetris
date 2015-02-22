#pragma once

#include <vector>
#include <functional>
#include "GameStructures.h"

class Tetramino;

class TetraminosPositionsDelegate
{
public:
	TetraminosPositionsDelegate(std::vector< std::vector<Tetramino*> > *tetraminos);
	~TetraminosPositionsDelegate(void);

	GamePositionOnBoard getTetraminoPosition(Tetramino *aTetramino);
	Tetramino* getTetraminoForXYposition(int xPosition, int yPosition);
	std::vector <GamePositionOnBoard> getAvailableTetraminis();
	std::vector <GamePositionOnBoard> getTetraminosForType(TetraminoType aTetraminoType);

private:

	typedef bool (TetraminosPositionsDelegate::*predicateFunction)(TetraminoType aFirstType, TetraminoType aSecondType);

	std::vector< std::vector<Tetramino*> > *_tetraminos;
	int _gameBoardHeight;
	int _gameBoardWidth;

	std::vector <GamePositionOnBoard> findAllTetraminisForPredicate(std::function<bool(Tetramino *aTetramino)> aPredicateFunction);
	std::vector <GamePositionOnBoard> getTetraminosInRowWithPredicate(int yPosition, std::function<bool(Tetramino *aTetramino)> aPredicateFunction);

	bool checkTetraminoInRow(Tetramino *aTetramino, int xPosition);
	GamePositionOnBoard getTetraminoPositionInRow(Tetramino *aTetramino, int xPosition);

};

