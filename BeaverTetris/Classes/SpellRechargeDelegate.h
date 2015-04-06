#pragma once

#include <string>

class SpellRechargeDelegate
{
public:
	SpellRechargeDelegate(std::string spellKey);
	~SpellRechargeDelegate(void);

	void updateSpell();
	float getSpellRechargePercent();
	void spellWasCasted();
	bool spellRecharged();

private:

	int _spellRechargeInterval;
	int _rechargeState;

};

