#include "GameBoardController.h"
#include "GameBoardViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"
#include "TetraminoViewController.h"

using namespace std;
using namespace cocos2d;

GameBoardController::GameBoardController(void)
{
	_gameBoardViewDataSource = new GameBoardViewDataSource();
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_tetraminosViews = getTetraminosViews();
	addTetraminoViewsToController();
	redrawGameBoard();
}


GameBoardController::~GameBoardController(void)
{
	delete _gameBoardViewDataSource;
}

vector<TetraminoViewController*> GameBoardController::getTetraminosViews()
{
	vector<TetraminoViewController*> tetraminosViews;

	int tetraminosCount = _gameBoardViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		TetraminoViewController *tetraminoView = new TetraminoViewController();
		Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(tetraminoIndex);
		tetraminoView->setPosition(tetraminoViewPosition);
		tetraminosViews.push_back(tetraminoView);
	}
	return tetraminosViews;
}

void GameBoardController::addTetraminoViewsToController()
{
	vector<TetraminoViewController*>::iterator viewsIterator;
	for (viewsIterator = _tetraminosViews.begin(); viewsIterator != _tetraminosViews.end(); viewsIterator++)
	{
		TetraminoViewController *view = *viewsIterator;
		this->addChild(view);
	}
}

void GameBoardController::redrawGameBoard()
{
	if (_gameTimeStepController->getUpdataAvailable())
	{
		updateTetraminoViews();
	}
}

void GameBoardController::updateTetraminoViews()
{
	hideAllTetraminos();
	updateGameBoardView();
}

void GameBoardController::hideAllTetraminos()
{
	vector<TetraminoViewController*>::iterator viewsIterator;
	for (viewsIterator = _tetraminosViews.begin(); viewsIterator != _tetraminosViews.end(); viewsIterator++)
	{
		TetraminoViewController *tetraminoView = (*viewsIterator);
		tetraminoView->setVisible(false);
	}
}

void GameBoardController::updateGameBoardView()
{
	int tetraminosCount = _gameBoardViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		if (_gameBoardViewDataSource->availableTetraminoOnIndex(tetraminoIndex))
		{
			string tetraminoTexture = _gameBoardViewDataSource->getTetraminoImageForIndex(tetraminoIndex);
			drawTetraminoTextureOnIndex(tetraminoTexture , tetraminoIndex);
		}
	}
}

void GameBoardController::drawTetraminoTextureOnIndex(string aTetraminoTextureKey, int aTetraminoIndex)
{
	if (aTetraminoIndex < _tetraminosViews.size())
	{
		TetraminoViewController *tetraminoView = _tetraminosViews[aTetraminoIndex];
		tetraminoView->setVisible(true);
		tetraminoView->setTexture(aTetraminoTextureKey);
		setLivesCountInTetraminoViewForIndex(tetraminoView, aTetraminoIndex);
	}
}

void GameBoardController::setLivesCountInTetraminoViewForIndex(TetraminoViewController* aTetraminoView, int aTetraminoIndex)
{
	string tetraminoLivesCount = string();
	if (_gameBoardViewDataSource->availableLevesCountOnIndex(aTetraminoIndex))
	{
		tetraminoLivesCount = _gameBoardViewDataSource->getTetraminoLivesCountForIndex(aTetraminoIndex);
	}
	aTetraminoView->setLivesCount(tetraminoLivesCount);
}

void GameBoardController::cleanTetraminoOnIndex(int aTetraminoIndex)
{
	if (aTetraminoIndex >= 0 && aTetraminoIndex < _tetraminosViews.size())
	{
		TetraminoViewController *tetraminoView = _tetraminosViews[aTetraminoIndex];
		tetraminoView->setVisible(false);
	}
}

