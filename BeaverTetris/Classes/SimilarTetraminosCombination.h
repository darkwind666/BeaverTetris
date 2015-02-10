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
class SimilarTetraminosCombinationDelegate;

class SimilarTetraminosCombination : public ServiceInterface
{
public:
	SimilarTetraminosCombination(GameBoard *aGameBoard);
	~SimilarTetraminosCombination(void);

	void checkSimilarTetraminosCombination();
	void setDelegate(SimilarTetraminosCombinationDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	TetraminosCombinatorDelegate *_tetraminosCombinatorDelegate;
	DetailsFromBoardDataSource *_detailsFromBoardDataSource;
	SimilarTetraminosCombinationDelegate *_delegate;

	void checkChainInDetailElements(std::vector<GamePositionOnBoard> aTetraminos);
	void checkChainInDetailHorisontals(std::vector<GamePositionOnBoard> aTetraminos);
	std::vector<GamePositionOnBoard> getChainInDetailHorisontal(TetraminoDetail *aDetail, int yPosition);
	std::vector<GamePositionOnBoard> getChainFromTetraminosPositions(std::vector<GamePositionOnBoard> aPositions, TetraminoDetail *aDetail);
	void sortChains(std::vector< std::vector<GamePositionOnBoard> > &aChains);
	void cleanChain(std::vector<GamePositionOnBoard> aPositions);

	void checkChainInDetailVerticals(std::vector<GamePositionOnBoard> aTetraminos);
	std::vector<GamePositionOnBoard> getChainInDetailVertical(TetraminoDetail *aDetail, int xPosition);

	void setAwardToPlayerFromTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void setTetraminosAward(std::vector<GamePositionOnBoard> aTetraminos);
	int getAwardForChainForTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void removeTetraminosWithPositions(std::vector<GamePositionOnBoard> aTetraminos);

	void sendMassageToDelegateWithTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void sendRemoveTetraminosMassagesToDelegate(std::vector<GamePositionOnBoard> aTetraminos);
	void sendCallbackWithAwardForTetraminosToDelegate(std::vector<GamePositionOnBoard> aTetraminos);

};

