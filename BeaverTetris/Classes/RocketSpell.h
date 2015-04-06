#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"

class CurrentDetailDataSource;
class RocketSpellDelegate;
class TetraminoRemovingObserverInterface;
class SpellRechargeDelegate;

class RocketSpell :public SpellInterface, public ServiceInterface
{
public:
	RocketSpell(void);
	~RocketSpell(void);

	virtual bool spellAvailable();
	virtual void castSpell();
	virtual void updateSpell();
	virtual float getSpellRechargePercent();

	void setDelegate(RocketSpellDelegate *aDelegate);
	void addObserver(TetraminoRemovingObserverInterface *aObserver);

private:

	CurrentDetailDataSource *_currentDetailDataSource;
	RocketSpellDelegate *_delegate;
	TetraminoRemovingObserverInterface *_observer;
	SpellRechargeDelegate *_spellRechargeDelegate;

	void sendMessageToDelegate();
	void sendMessageToObserver();
	void sendMessageToObserverAboutRemovingTetraminos();
	void sendMessageToObserverWithDetailLine(int aLine);

};

