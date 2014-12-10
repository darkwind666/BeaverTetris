#pragma once

#include "TetraminisDetailsFactory.h"
#include "ActiveDetails.h"
#include "GameBoard.h"

class CollisionDelegate;

class CurrentDetailController
{
public:
	CurrentDetailController(TetraminisDetailsFactory *detailsFactory, ActiveDetails *activeDetailsStore, GameBoard *aGameBoard);
	~CurrentDetailController(void);

	void makeNewDetail(void);
	void moveLeftDetail(void);
	void moveRightDetail(void);
	void rotateDetail(void);
	void removeCurrentDetail();
	void setUnAvailableCurrentDetail();
	bool availableCurrentDetail();


private:

	TetraminisDetailsFactory *_detailsFactory;
	ActiveDetails *_activeDetailsStore;
	TetraminoDetail *_currentDetail;
	GameBoard *_gameBoard;
	CollisionDelegate *_collisionDelegate;

	void setNewPositionIfNoCollision(GamePositionOnBoard aNewDetailPosition);
	bool collideWithOtherTetraminos(TetraminoDetail aDetail);

};

