#pragma once

#include "GameSystemInterface.h"
#include "GameBoard.h"

class RemovingDeadTetraminosSystem :public GameSystemInterface
{
public:
	RemovingDeadTetraminosSystem(GameBoard *aGameBoard);
	~RemovingDeadTetraminosSystem(void);

	void updateSystem(float deltaTime);

private:

	GameBoard *_gameBoard;

};

