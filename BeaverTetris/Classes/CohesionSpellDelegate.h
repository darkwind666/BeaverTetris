#pragma once

#include "GameStructures.h"

class CohesionSpellDelegate
{
public:
	CohesionSpellDelegate(void);
	~CohesionSpellDelegate(void);

	virtual void makeTetraminoOnPosition(GamePositionOnBoard aPosition) = 0;

};

