#pragma once

#include <vector>
#include "GameStructures.h"

class TetraminoDetail;
class GameBoard;

class TetraminosCombinatorDelegate
{
public:
	TetraminosCombinatorDelegate(GameBoard *aGameBoard);
	~TetraminosCombinatorDelegate(void);

	TetraminoDetail* combineTetraminosInDetail(std::vector <GamePositionOnBoard> aDetailElements);
	std::vector <TetraminoDetail*> combineTetraminosInDetails(std::vector < std::vector <GamePositionOnBoard> > aTetraminoDetailsInGame);

private:

	GameBoard *_gameBoard;

	GamePositionOnBoard getMaxDetailPositionFromDetailsElements(std::vector <GamePositionOnBoard> aDetailElements);
	GamePositionOnBoard getMinDetailPositionFromDetailsElements(std::vector <GamePositionOnBoard> aDetailElements);
	GamePositionOnBoard getDetailSizeFromMaxAndMinPosition(GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition);
	TetraminoDetail* getDetailWithMaxAndMinPosition(std::vector <GamePositionOnBoard> aDetailElements, GamePositionOnBoard aMaxPosition, GamePositionOnBoard aMinPosition);
	void fillDetailWithTetraminos(TetraminoDetail *aDetail, std::vector <GamePositionOnBoard> aDetailElements);

};

