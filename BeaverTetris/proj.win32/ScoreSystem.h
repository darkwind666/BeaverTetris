#pragma once

#include "GameSystemInterface.h"
#include "FullLineCombination.h"
#include "SimilarTetraminosCombination.h"

class ScoreSystem :public GameSystemInterface
{
public:
	ScoreSystem(GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource);
	~ScoreSystem(void);

	void updateSystem(float deltaTime);

private:


	FullLineCombination *_fullLineCombination;
	SimilarTetraminosCombination *_similarTetraminosCombination;

};

