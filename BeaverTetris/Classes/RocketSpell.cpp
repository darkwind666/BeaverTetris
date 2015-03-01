#include "RocketSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "RocketSpellDelegate.h"
#include "TetraminoRemovingObserverInterface.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"

RocketSpell::RocketSpell(void)
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_delegate = NULL;
	_observer = NULL;
}


RocketSpell::~RocketSpell(void)
{
}

bool RocketSpell::spellAvailable()
{
	return _currentDetailDataSource->currentDetailAvailable();
}

void RocketSpell::castSpell()
{
	sendMessageToDelegate();
	sendMessageToObserver();
	_currentDetailDataSource->removeCurrentDetail();
}

void RocketSpell::sendMessageToDelegate()
{
	if (_delegate)
	{
		_delegate->removeCurrentDetail();
	}
}

void RocketSpell::setDelegate(RocketSpellDelegate *aDelegate)
{
	_delegate = aDelegate;
}

void RocketSpell::sendMessageToObserver()
{
	if (_observer)
	{
		sendMessageToObserverAboutRemovingTetraminos();
	}
}

void RocketSpell::sendMessageToObserverAboutRemovingTetraminos()
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	int detailHeight = currentDetail->getDetailWidth();
	for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
	{
		sendMessageToObserverWithDetailLine(heightIndex);
	}
}

void RocketSpell::sendMessageToObserverWithDetailLine(int aLine)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	int detailWidth = currentDetail->getDetailWidth();
	for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
	{
		Tetramino *tetraminoInDetail = currentDetail->getTetraminoForXY(widthIndex, aLine);
		_observer->tetraminoRemoving(tetraminoInDetail);
	}
}

void RocketSpell::addObserver(TetraminoRemovingObserverInterface *aObserver)
{
	_observer = aObserver;
}

