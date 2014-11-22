#pragma once
class SpellInterface
{
public:
	SpellInterface(void);
	~SpellInterface(void);

	virtual void castSpell(void) = 0;

};

