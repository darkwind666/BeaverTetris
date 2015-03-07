#pragma once

#include "ServiceInterface.h"
#include <vector>
#include "GameStructures.h"

class Tetramino;
class TetraminosPositionsDelegate;
class TetraminoRemovingObserverInterface;
class TetraminosFactory;

class GameBoard : public ServiceInterface
{
public:
	GameBoard(int width, int height);
	~GameBoard(void);

	void setTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition);
	void replaceTetraminoXYposition(Tetramino *aTetramino, int xPosition, int yPosition);

	int getGameBoardWidth();
	int getGameBoardHeight();

	Tetramino* getTetraminoForXYposition(int xPosition, int yPosition);
	GamePositionOnBoard getTetraminoPosition(Tetramino *aTetramino);
	GamePositionOnBoard getPositionForIndex(int aIndex);
	int getIndexForPosition(GamePositionOnBoard aPosition);

	bool positionInBoard(GamePositionOnBoard aPosition);

	std::vector <GamePositionOnBoard> getAvailableTetraminis();
	std::vector <GamePositionOnBoard> getTetraminosForType(TetraminoType aTetraminoType);

	void removeTetraminoForXYposition(int xPosition, int yPosition);
	void removeTetraminoForXYpositionIfItHasNoLives(int xPosition, int yPosition);
	void removeTetraminos(std::vector <GamePositionOnBoard> aNeedToRemoveTetraminos);
	void deleteAllTetraminos();
	
	void addObserver(TetraminoRemovingObserverInterface *aObserver);

private:

	int _gameBoardWidth;
	int _gameBoardHeight;
	std::vector< std::vector<Tetramino*> > _tetramins;
	TetraminoRemovingObserverInterface *_observer;
	TetraminosPositionsDelegate *_tetraminosSourceDelegate;
	TetraminosFactory *_tetraminosFactory;

	void cleanGameBoard(void);

};

