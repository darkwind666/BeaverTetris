#include "GameBoardController.h"
#include "GameBoardViewDataSource.h"
#include "TetraminoColorsDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"

using namespace std;
using namespace cocos2d;

GameBoardController::GameBoardController(void)
{
	_gameBoardViewDataSource = new GameBoardViewDataSource();
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_tetraminoColorsDataSource = new TetraminoColorsDataSource();
	_tetraminosViews = getTetraminosViews();
	addTetraminoViewsToController();
	redrawGameBoard();
}


GameBoardController::~GameBoardController(void)
{
}

vector<Sprite*> GameBoardController::getTetraminosViews()
{
	vector<Sprite*> tetraminosViews;

	int tetraminosCount = _gameBoardViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		Sprite *tetraminoView = Sprite::create();
		Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(tetraminoIndex);
		tetraminoView->setPosition(tetraminoViewPosition);
		tetraminosViews.push_back(tetraminoView);
	}
	return tetraminosViews;
}

void GameBoardController::addTetraminoViewsToController()
{
	vector<Sprite*>::iterator viewsIterator;
	for (viewsIterator = _tetraminosViews.begin(); viewsIterator != _tetraminosViews.end(); viewsIterator++)
	{
		this->addChild(*viewsIterator);
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
	vector<Sprite*>::iterator viewsIterator;
	for (viewsIterator = _tetraminosViews.begin(); viewsIterator != _tetraminosViews.end(); viewsIterator++)
	{
		Sprite *tetraminoView = (*viewsIterator);
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

void GameBoardController::drawTetraminoTextureOnIndex(std::string aTetraminoTextureKey, int aTetraminoIndex)
{
	if (aTetraminoIndex < _tetraminosViews.size())
	{
		Sprite *tetraminoView = _tetraminosViews[aTetraminoIndex];
		tetraminoView->setVisible(true);
		tetraminoView->setTexture("HelloWorld.png");
		tetraminoView->setScaleX(0.05f);
		tetraminoView->setScaleY(0.08f);
		
		Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(aTetraminoTextureKey);
		tetraminoView->setColor(tetraminoColor);
	}
}

void GameBoardController::cleanTetraminoOnIndex(int aTetraminoIndex)
{
	if (aTetraminoIndex >= 0 && aTetraminoIndex < _tetraminosViews.size())
	{
		Sprite *tetraminoView = _tetraminosViews[aTetraminoIndex];
		tetraminoView->setVisible(false);
	}
}
