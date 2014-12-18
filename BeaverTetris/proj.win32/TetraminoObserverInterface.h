#pragma once

class Tetramino;

class TetraminoObserverInterface
{
public:
	TetraminoObserverInterface(void);
	~TetraminoObserverInterface(void);

	virtual void tetraminoRemoving(Tetramino *aTetramino) = 0;

};

