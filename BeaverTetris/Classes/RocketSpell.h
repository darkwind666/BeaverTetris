#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"

class CurrentDetailDataSource;
class RocketSpellDelegate;

class RocketSpell :public SpellInterface, public ServiceInterface
{
public:
	RocketSpell(void);
	~RocketSpell(void);

	bool spellAvailable();
	void castSpell();
	void setDelegate(RocketSpellDelegate *aDelegate);

private:

	CurrentDetailDataSource *_currentDetailDataSource;
	RocketSpellDelegate *_delegate;

};

