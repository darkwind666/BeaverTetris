#pragma once

#include <vector>
#include "ServiceInterface.h"
#include "GameStructures.h"

class GameBoard;
class TetraminoDetail;
class Tetramino;
class CurrentPlayerDataSource;
class AwardForTetraminoDataSource;
class TetraminosCombinatorDelegate;
class DetailsFromBoardDataSource;

class SimilarTetraminosCombination : public ServiceInterface
{
public:
	SimilarTetraminosCombination(GameBoard *aGameBoard);
	~SimilarTetraminosCombination(void);

	void checkSimilarTetraminosCombination();

private:

	GameBoard *_gameBoard;
	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	CurrentPlayerDataSource *_currentPlayerDataSource;

	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;

	bool checkChainInDetail(TetraminoDetail *aDetail);
	bool checkChainInDetailHorisontals(TetraminoDetail *aDetail);
	int getChainInDetailHorisontal(TetraminoDetail *aDetail, int yPosition);
	int getChainCountFromTetraminos(std::vector<Tetramino*> aTetraminos);
	bool checkChainInDetailVerticals(TetraminoDetail *aDetail);
	int getChainInDetailVertical(TetraminoDetail *aDetail, int xPosition);
	int getAwardForChainForTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void removeTetraminosWithPositions(std::vector<GamePositionOnBoard> aTetraminos);

};

