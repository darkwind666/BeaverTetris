#pragma once

#include <vector>

class GameBoard;
class NewTetraminoDetailDataSource;
class TetraminoDetailLocatorDelegate;
class CollisionDelegate;
class TetraminoDetail;

class TetraminosFallEvent
{
public:
	TetraminosFallEvent(void);
	~TetraminosFallEvent(void);

	void updateEvent(void);

private:

	int _currentUpdateState;
	GameBoard *_gameBoard;
	NewTetraminoDetailDataSource *_newTetraminoDetailDataSource;
	CollisionDelegate *_collisionDelegate;
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;

	std::vector<TetraminoDetail*> getTetraminoDetailsForFalling();
	TetraminoDetail* getNewDetail();
	void setDetailPosition(TetraminoDetail *aDetail);
	void placeDetailsOnGameBoard(std::vector<TetraminoDetail*> aTetraminoDetails);

};

