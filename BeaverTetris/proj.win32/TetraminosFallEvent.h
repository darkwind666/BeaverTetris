#pragma once

#include "GameEventInterface.h"
#include "GameBoard.h"
#include <vector>
#include "TetraminisDetailsFactory.h"
#include "TetraminoDetailLocatorDelegate.h"

class TetraminosFallEvent :public GameEventInterface
{
public:
	TetraminosFallEvent(void);
	~TetraminosFallEvent(void);

	bool eventTime(void);
	void runEvent(void);
	void updateEvent(void);

private:

	int _currentUpdateState;
	GameBoard *_gameBoard;
	TetraminisDetailsFactory *_tetraminisDetailsFactory;
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;

	std::vector<TetraminoDetail*> getTetraminoDetailsForFalling();
	TetraminoDetail* getNewDetailFromWidthIndex(int aWidthIndex);
	void placeDetailsOnGameBoard(std::vector<TetraminoDetail*> aTetraminoDetails);

};

