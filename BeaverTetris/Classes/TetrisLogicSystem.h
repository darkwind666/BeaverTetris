#pragma once

#include "GameSystemInterface.h"

class GameBoard;
class FullLineCombination;
class SimilarTetraminosCombination;

class TetrisLogicSystem :public GameSystemInterface
{
public:
	TetrisLogicSystem(GameBoard *aGameBoard);
	~TetrisLogicSystem(void);

	void updateSystem(float deltaTime);

private:


	FullLineCombination *_fullLineCombination;
	SimilarTetraminosCombination *_similarTetraminosCombination;

};

