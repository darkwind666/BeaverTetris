#pragma once

#include "SpellInterface.h"

class CurrentDetailDataSource;

class RocketSpell :public SpellInterface
{
public:
	RocketSpell(void);
	~RocketSpell(void);

	bool spellAvailable();
	void castSpell();

private:

	CurrentDetailDataSource *_currentDetailDataSource;

};

