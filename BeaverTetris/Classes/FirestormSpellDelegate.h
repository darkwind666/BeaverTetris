#pragma once

#include <vector>
#include "GameStructures.h"

class FirestormSpellDelegate
{
public:
	FirestormSpellDelegate(void);
	~FirestormSpellDelegate(void);

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions) = 0;
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition) = 0;

};

