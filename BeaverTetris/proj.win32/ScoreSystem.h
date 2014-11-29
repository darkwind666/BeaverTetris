#pragma once

#include "GameSystemInterface.h"
#include "AwardForTetraminoDataSource.h"
#include "GameBoard.h"
#include "CurrentPlayerDataSource.h"
#include "TetraminosSeparatorDelegate.h"

class ScoreSystem :public GameSystemInterface
{
public:
	ScoreSystem(AwardForTetraminoDataSource *aAwardForTetraminoDataSource, GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource, TetraminosSeparatorDelegate *aTetraminosSeparatorDelegate);
	~ScoreSystem(void);

	void updateSystem(float deltaTime);

private:

	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	GameBoard *_gameBoard;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	TetraminosSeparatorDelegate *_tetraminosSeparatorDelegate;

	bool fullLineCheck(int lineIndex);
	int getAwardForTetramino(Tetramino aTetramino);
	void removeKilledTetraminos(int lineIndex);
	bool _someObjectWasDeletedIndicator;

};

