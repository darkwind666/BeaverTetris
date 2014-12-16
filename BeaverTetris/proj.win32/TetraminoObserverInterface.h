#pragma once

#include "Tetramino.h"

class TetraminoObserverInterface
{
public:
	TetraminoObserverInterface(void);
	~TetraminoObserverInterface(void);

	virtual void tetraminoRemoving(Tetramino *aTetramino);

};

