#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"

class CurrentDetailDataSource;
class RocketSpellDelegate;
class TetraminoRemovingObserverInterface;

class RocketSpell :public SpellInterface, public ServiceInterface
{
public:
	RocketSpell(void);
	~RocketSpell(void);

	bool spellAvailable();
	void castSpell();
	void setDelegate(RocketSpellDelegate *aDelegate);
	void addObserver(TetraminoRemovingObserverInterface *aObserver);

private:

	CurrentDetailDataSource *_currentDetailDataSource;
	RocketSpellDelegate *_delegate;
	TetraminoRemovingObserverInterface *_observer;

	void sendMessageToDelegate();
	void sendMessageToObserver();
	void sendMessageToObserverAboutRemovingTetraminos();
	void sendMessageToObserverWithDetailLine(int aLine);

};

