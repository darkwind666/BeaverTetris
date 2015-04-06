#pragma once

#include "GameSystemInterface.h"

class SpellBox;

class SpellRechargeSystem : public GameSystemInterface
{
public:
	SpellRechargeSystem(void);
	~SpellRechargeSystem(void);

	virtual void updateSystem(float deltaTime);

private:

	SpellBox *_spellBox;

};

