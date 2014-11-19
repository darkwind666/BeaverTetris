#include "ServiceLocator.h"

static GameViewElementsDataSource  *_gameViewElementsDataSource;
static GameTransitionsController *_gameTransitionsController;


GameViewElementsDataSource*  ServiceLocator::getGameViewElementsDataSource()
{
	return _gameViewElementsDataSource;
}

void ServiceLocator::setGameViewElementsDataSource(GameViewElementsDataSource *aGameViewElementsDataSource)
{
	_gameViewElementsDataSource = aGameViewElementsDataSource;
}



GameTransitionsController*  ServiceLocator::getGameTransitionsController()
{
	return _gameTransitionsController;
}

void ServiceLocator::setGameTransitionsController(GameTransitionsController *aGameTransitionsController)
{
	_gameTransitionsController = aGameTransitionsController;
}
