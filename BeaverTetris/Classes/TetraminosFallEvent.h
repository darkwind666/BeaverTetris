#pragma once

#include "ServiceInterface.h"
#include <vector>
#include "GameStructures.h"

class GameBoard;
class NewTetraminoDetailDataSource;
class TetraminoDetailLocatorDelegate;
class CollisionDelegate;
class TetraminoDetail;
class TetraminosFallEventDelegate;

class TetraminosFallEvent : public ServiceInterface
{
public:
	TetraminosFallEvent(void);
	~TetraminosFallEvent(void);

	void updateEvent(void);
	void setDelegate(TetraminosFallEventDelegate *aDelegate);

private:

	int _currentUpdateState;
	GameBoard *_gameBoard;
	NewTetraminoDetailDataSource *_newTetraminoDetailDataSource;
	CollisionDelegate *_collisionDelegate;
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;
	TetraminosFallEventDelegate *_delegate;

	std::vector<TetraminoDetail*> getTetraminoDetailsForFalling();
	TetraminoDetail* getNewDetail();
	void setDetailPosition(TetraminoDetail *aDetail);
	void placeDetailsOnGameBoard(std::vector<TetraminoDetail*> aTetraminoDetails);
	void sendMessageToDelegateWithDetailAndCollisionPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);

};

