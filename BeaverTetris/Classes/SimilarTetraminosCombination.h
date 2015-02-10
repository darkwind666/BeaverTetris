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

	bool checkChainInDetail(TetraminoDetail *aDetail);
	bool checkChainInDetailHorisontals(TetraminoDetail *aDetail);
	int getChainInDetailHorisontal(TetraminoDetail *aDetail, int yPosition);
	int getChainCountFromTetraminos(std::vector<Tetramino*> aTetraminos);
	bool checkChainInDetailVerticals(TetraminoDetail *aDetail);
	int getChainInDetailVertical(TetraminoDetail *aDetail, int xPosition);
	void setAwardToPlayerFromTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void setTetraminosAward(std::vector<GamePositionOnBoard> aTetraminos);
	int getAwardForChainForTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void removeTetraminosWithPositions(std::vector<GamePositionOnBoard> aTetraminos);

	void sendMassageToDelegateWithTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void sendRemoveTetraminosMassagesToDelegate(std::vector<GamePositionOnBoard> aTetraminos);
	void sendCallbackWithAwardForTetraminosToDelegate(std::vector<GamePositionOnBoard> aTetraminos);

};

