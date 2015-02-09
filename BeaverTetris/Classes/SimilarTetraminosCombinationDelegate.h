#pragma once

#include "GameStructures.h"
#include <vector>

class SimilarTetraminosCombinationDelegate
{
public:
	SimilarTetraminosCombinationDelegate(void);
	~SimilarTetraminosCombinationDelegate(void);

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions) = 0;
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition) = 0;
	virtual void setCallback(std::function<void()> aCallback) = 0;

};

