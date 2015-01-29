#pragma once

#include "ServiceInterface.h"
#include "GameSystemInterface.h"
#include "GameStructures.h"
#include <functional>

class GameBoard;
class CollisionDelegate;
class TetraminoDetailLocatorDelegate;
class CurrentDetailDataSource;
class TetraminoDetail;


class CurrentDetailController : public GameSystemInterface, public ServiceInterface
{
public:
	CurrentDetailController(GameBoard *aGameBoard, CurrentDetailDataSource *aDetailDataSource);
	~CurrentDetailController(void);

	void moveLeftDetail(void);
	void moveRightDetail(void);
	void rotateDetail(void);
	void throwDetailOnGameBoard();

	virtual void updateSystem(float deltaTime);

private:

	GameBoard *_gameBoard;
	CollisionDelegate *_collisionDelegate;
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;
	CurrentDetailDataSource *_currentDetailDataSource;

	TetraminoDetail* getCurrentDetail();
	GamePositionOnBoard getCurrentDetailPosition();

	void moveDownDetail();
	bool checkCollisionForCurrentDetailWithNewPosition(GamePositionOnBoard aNewDetailPosition);
	bool checkCollisionForDetail(TetraminoDetail *aDetail);
	void setNewDetailPosition(GamePositionOnBoard aNewDetailPosition);

	void makeOperationWithCurrentDetail(std::function<void()> aOperation);
	void writeCurrentDetailInBoardAndRemove();

};

