#pragma once

#include "GameSystemInterface.h"

class GameBoard;
class FullLineCombination;
class FillingGapInBoardSystem;

class TetrisLogicSystem :public GameSystemInterface
{
public:
	TetrisLogicSystem(GameBoard *aGameBoard);
	~TetrisLogicSystem(void);

	void updateSystem(float deltaTime);

private:


	FullLineCombination *_fullLineCombination;
	FillingGapInBoardSystem *_fillingGapInBoardDelegate;

};

