#include "Tetramino.h"
#include "stdlib.h"

Tetramino::Tetramino(void)
{
	_tetraminoType = kTetraminoEmpty;
	_tetraminoObserver = NULL;
	_tetraminoLivesCount = 0;
}

Tetramino::Tetramino(TetraminoType aType)
{
	_tetraminoType = aType;
	_tetraminoObserver = NULL;
	_tetraminoLivesCount = 1;
}

Tetramino::Tetramino(TetraminoType aType, int aLivesCount)
{
	_tetraminoType = aType;
	_tetraminoLivesCount = aLivesCount;
	_tetraminoObserver = NULL;
}

Tetramino::~Tetramino(void)
{
	if (_tetraminoObserver != NULL)
	{
		_tetraminoObserver->tetraminoRemoving(this);
	}
}


TetraminoType Tetramino::getTetraminoType(void)
{
	return _tetraminoType;
}

int Tetramino::getTetraminoCost(void)
{
	return _tetraminoCost;
}


int Tetramino::getTetraminoLivesCount(void)
{
	return _tetraminoLivesCount;
}

void Tetramino::reduceLive(void)
{
	_tetraminoLivesCount--;
}

void Tetramino::setLivesToZero()
{
	_tetraminoLivesCount = 0;
}

void Tetramino::addObserver(TetraminoObserverInterface *aTetraminoObserverInterface)
{
	_tetraminoObserver = aTetraminoObserverInterface;
}

void Tetramino::removeObserver(TetraminoObserverInterface *aTetraminoObserverInterface)
{
	if (_tetraminoObserver == aTetraminoObserverInterface)
	{
		_tetraminoObserver = NULL;
	}

}
