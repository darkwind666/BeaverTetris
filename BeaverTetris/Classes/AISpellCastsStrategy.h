#pragma once

#include <vector>

class SpellInterface;

class AISpellCastsStrategy
{
public:
	AISpellCastsStrategy();
	~AISpellCastsStrategy(void);

	void updateAI();

private:

	int _currentUpdateState;
	std::vector<SpellInterface*> _spells;

	std::vector<SpellInterface*> getSpells();
	void castSpell();

};

