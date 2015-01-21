#pragma once

#include "ServiceInterface.h"
#include <vector>
#include "GameStructures.h"
#include "GameBoardObserverInterface.h"
#include "TetraminosPositionsDelegate.h"

class Tetramino;

class GameBoard : public ServiceInterface
{
public:
	GameBoard(int width, int height);
	~GameBoard(void);

	void setTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition);

	int getGameBoardWidth();
	int getGameBoardHeight();

	Tetramino* getTetraminoForXYposition(int xPosition, int yPosition);
	GamePositionOnBoard getTetraminoPosition(Tetramino *aTetramino);

	std::vector <GamePositionOnBoard> getAvailableTetraminis();
	std::vector <GamePositionOnBoard> getTetraminisForType(TetraminoType aTetraminoType);

	void removeTetraminoForXYposition(int xPosition, int yPosition);
	void removeTetraminos(std::vector <GamePositionOnBoard> aNeedToRemoveTetraminos);
	void cleanTetraminoRowForYposition(int yPosition);
	void cleanGameBoard(void);

	void addObserver(GameBoardObserverInterface *aGameBoardObserver);
	void removeObserver(GameBoardObserverInterface *aGameBoardObserver);

private:

	typedef bool (GameBoard::*predicateFunction)(TetraminoType aFirstType, TetraminoType aSecondType);

	Tetramino **_tetramins;
	int _gameBoardWidth;
	int _gameBoardHeight;
	GameBoardObserverInterface *_gameBoardObserver;
	TetraminosPositionsDelegate *_tetraminosSourceDelegate;

};

