#pragma once
#include "SpellInterface.h"
class AddLineToBoardBottomSpell :public SpellInterface
{
public:
	AddLineToBoardBottomSpell(void);
	~AddLineToBoardBottomSpell(void);

	bool spellAvailable(void);
	void castSpell();

};

