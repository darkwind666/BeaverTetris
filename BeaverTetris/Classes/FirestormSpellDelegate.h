#pragma once

#include <vector>
#include "GameStructures.h"

class FirestormSpellDelegate
{
public:
	FirestormSpellDelegate(void);
	virtual ~FirestormSpellDelegate(void);

	virtual void blowUpTetraminosAreaOnPosition(std::vector<GamePositionOnBoard> tetraminosPositions, GamePositionOnBoard aPosition) = 0;
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition) = 0;
	virtual void removeCurrentDetailWithExplosionPosition(GamePositionOnBoard aPosition) = 0;

};

