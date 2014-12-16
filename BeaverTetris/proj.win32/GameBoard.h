#pragma once

#include <vector>
#include "GameStructures.h"
#include "Tetramino.h"
#include "GameBoardObserverInterface.h"

class GameBoard
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

	vector <GamePositionOnBoard> findAllTetraminisForTypeAndPredicate(TetraminoType aTetraminoType, predicateFunction aPredicateFunction);
	bool equalType(TetraminoType aFirstType, TetraminoType aSecondType);
	bool largerType(TetraminoType aFirstType, TetraminoType aSecondType);
};

