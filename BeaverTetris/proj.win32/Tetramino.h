#pragma once

#include "GameEnums.h"

class Tetramino
{
public:
	Tetramino(void);
	~Tetramino(void);

	TetraminoType getTetraminoType(void);
	int getTetraminoCost(void);

	int getTetraminoLivesCount(void);
	void reduceLive(void);

};

