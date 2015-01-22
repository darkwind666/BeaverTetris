#pragma once

#include "Tetramino.h"

class GameBoardObserverInterface
{
public:
	GameBoardObserverInterface(void);
	~GameBoardObserverInterface(void);

	virtual void tetraminoRemoving(Tetramino *aTetramino) = 0;

};

