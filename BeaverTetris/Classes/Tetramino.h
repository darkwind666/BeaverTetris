#pragma once

#include "GameEnums.h"
#include "TetraminoObserverInterface.h"

class Tetramino
{
public:
	Tetramino(void);
	Tetramino(TetraminoType aType);
	Tetramino(TetraminoType aType, int aLivesCount);
	~Tetramino(void);

	TetraminoType getTetraminoType(void);
	int getTetraminoCost(void);

	int getTetraminoLivesCount(void);
	void reduceLive(void);
	void setLivesToZero();

	void addObserver(TetraminoObserverInterface *aTetraminoObserverInterface);
	void removeObserver(TetraminoObserverInterface *aTetraminoObserverInterface);

private:

	TetraminoType _tetraminoType;
	int _tetraminoCost;
	int _tetraminoLivesCount;
	TetraminoObserverInterface *_tetraminoObserver;

};

