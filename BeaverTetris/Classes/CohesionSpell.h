#pragma once

#include "SpellInterface.h"
#include <vector>
#include "GameStructures.h"

class GameBoard;

class CohesionSpell :public SpellInterface
{
public:
	CohesionSpell(void);
	~CohesionSpell(void);

	virtual bool spellAvailable(void);
	virtual void castSpell();

private:

	GameBoard *_gameBoard;

	std::vector<GamePositionOnBoard> getEmptyTetraminosForCohesion();

	std::vector<GamePositionOnBoard> getEmptyTetraminosPositionsAroundPosition(GamePositionOnBoard aPosition);
	std::vector<GamePositionOnBoard> getTetraminosAroundPosition(GamePositionOnBoard aPosition);
	std::vector<GamePositionOnBoard> getEmptyTetraminosPositionsWithoutBorder(std::vector<GamePositionOnBoard> tetraminosPositions);
	void setTetraminoPositionInPositions(GamePositionOnBoard aPosition, std::vector<GamePositionOnBoard> &tetraminosPositions);
	void setTetraminosInTetraminosForCohesion(std::vector<GamePositionOnBoard> &tetraminosPositions, std::vector<GamePositionOnBoard> &tetraminosForCohesion);
	void setPositionInTetraminosForCohesion(GamePositionOnBoard aPosition, std::vector<GamePositionOnBoard> &tetraminosForCohesion);
	void setTetraminoPositionInTetraminosForCohesion(GamePositionOnBoard aPosition, std::vector<GamePositionOnBoard> &tetraminosForCohesion);
	bool checkTetraminoPositionInPositions(GamePositionOnBoard aPosition, std::vector<GamePositionOnBoard> &aPositions);

	TetraminoType getRandomTetraminoType();
	void setNewTetraminoForPosition(GamePositionOnBoard aPosition);
	void setNewTetraminoForIndexInEmptyTetraminos(int tetraminoIndex, std::vector<GamePositionOnBoard> &emptyTetraminosForCohesion);

};

