#pragma once

#include <vector>
#include "GameStructures.h"

class ExplosionAnimationDelegate;
class CurrentPlayerDataSource;
class GameBoard;
class AwardForTetraminoDataSource;

class TetraminosChainCleaner
{
public:
	TetraminosChainCleaner(GameBoard *aGameBoard);
	~TetraminosChainCleaner(void);

	void cleanChain(std::vector<GamePositionOnBoard> aPositions);
	void setDelegate(ExplosionAnimationDelegate *aDelegate);

private:

	ExplosionAnimationDelegate *_delegate;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	GameBoard *_gameBoard;
	AwardForTetraminoDataSource *_awardForTetraminoDataSource;

	void setAwardToPlayerFromTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void setTetraminosAward(std::vector<GamePositionOnBoard> aTetraminos);
	int getAwardForChainForTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void removeTetraminosWithPositions(std::vector<GamePositionOnBoard> aTetraminos);
	
	void sendMassageToDelegateWithTetraminos(std::vector<GamePositionOnBoard> aTetraminos);
	void sendRemoveTetraminosMassagesToDelegate(std::vector<GamePositionOnBoard> aTetraminos);
	void sendCallbackWithAwardForTetraminosToDelegate(std::vector<GamePositionOnBoard> aTetraminos);

};

