#pragma once

#include <vector>
#include "GameStructures.h"

class DamageToPlayerSpellDelegate
{
public:
	DamageToPlayerSpellDelegate(void);
	~DamageToPlayerSpellDelegate(void);

	virtual void blowUpTetraminosForPositions(std::vector<GamePositionOnBoard> tetraminosPositions) = 0;
	virtual void removeTetraminoOnPositionXY(int xPosition, int yPosition) = 0;

};

