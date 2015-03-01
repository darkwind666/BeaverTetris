#pragma once

class Tetramino;

class TetraminoRemovingObserverInterface
{
public:
	TetraminoRemovingObserverInterface(void);
	virtual ~TetraminoRemovingObserverInterface(void);

	virtual void tetraminoRemoving(Tetramino *aTetramino) = 0;

};

