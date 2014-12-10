#pragma once

#include "SpellInterface.h"
#include "GameBoard.h"
#include <vector>
#include "GameStructures.h"

class CohesionSpell :public SpellInterface
{
public:
	CohesionSpell(void);
	~CohesionSpell(void);

	bool spellAvailable(void);
	void castSpell();

private:

	GameBoard *_gameBoard;
	bool _someTetraminosWasRemoved;

	std::vector<GamePositionOnBoard> getEmptyTetraminosForCohesion();

	std::vector<GamePositionOnBoard> getEmptyTetraminosPositionsAroundPosition(GamePositionOnBoard aPosition);
	std::vector<GamePositionOnBoard> getTetraminosAroundPosition(GamePositionOnBoard aPosition);
	std::vector<GamePositionOnBoard> getEmptyTetraminosPositionsWithoutBorder(std::vector<GamePositionOnBoard> emptyTetraminosPositions);
	void setNewEmptyTetraminosInEmptyTetraminosForCohesion(std::vector<GamePositionOnBoard> &newEmptyTetraminosPositions, std::vector<GamePositionOnBoard> &emptyTetraminosForCohesion);
	void setNewEmptyTetraminoInEmptyTetraminos(GamePositionOnBoard newTetraminoPosition, std::vector<GamePositionOnBoard> &emptyTetraminosForCohesion);
	
	TetraminoType getRandomTetraminoType();
	void setNewTetraminoForIndexInEmptyTetraminos(int tetraminoIndex, std::vector<GamePositionOnBoard> &emptyTetraminosForCohesion);

};

