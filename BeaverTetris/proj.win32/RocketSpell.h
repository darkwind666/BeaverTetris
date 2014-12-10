#pragma once

#include "SpellInterface.h"
#include "CurrentDetailController.h"

class RocketSpell :public SpellInterface
{
public:
	RocketSpell(void);
	~RocketSpell(void);

	bool spellAvailable();
	void castSpell();

private:

	CurrentDetailController *_currentDetailController;

};

