#include "GameBoardController.h"
#include "GameBoardViewDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;
using namespace cocos2d;

GameBoardController::GameBoardController(void)
{
	_gameBoardViewDataSource = new GameBoardViewDataSource();
	_redrawAvailable = true;
	_tetraminosColors = getTetraminosColors();
	_tetraminosViews = getTetraminosViews();
	addTetraminoViewsToController();
	redrawGameBoard();
}


GameBoardController::~GameBoardController(void)
{
}

map<string, Color3B> GameBoardController::getTetraminosColors()
{
	map<string, Color3B> tetraminosColors;

	tetraminosColors[redTetraminoKey] = Color3B::RED;
	tetraminosColors[greenTetraminoKey] = Color3B::GREEN;
	tetraminosColors[blueTetraminoKey] = Color3B::BLUE;
	tetraminosColors[goldTetraminoKey] = Color3B::YELLOW;
	tetraminosColors[blackTetraminoKey] = Color3B::BLACK;
	tetraminosColors[queenTetraminoKey] = Color3B::MAGENTA;
	tetraminosColors[princessTetraminoKey] = Color3B::GRAY;
	tetraminosColors[kingTetraminoKey] = Color3B::WHITE;

	return tetraminosColors;
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
	if (_redrawAvailable)
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
	Sprite *tetraminoView = _tetraminosViews[aTetraminoIndex];
	tetraminoView->setVisible(true);
	tetraminoView->setTexture("HelloWorld.png");
	
	Color3B tetraminoColor = getColorForKey(aTetraminoTextureKey);
	tetraminoView->setColor(tetraminoColor);
}

Color3B GameBoardController::getColorForKey(string aKey)
{
	string fileExtension = ".png";
	int fileExtensionPosition = aKey.find(fileExtension);
	string colorKey = aKey.erase(fileExtensionPosition + fileExtension.size());
	return _tetraminosColors[colorKey];
}

void GameBoardController::setRedrawAvailable(bool redrawAvailable)
{
	_redrawAvailable = redrawAvailable;
}

void GameBoardController::cleanTetraminoOnIndex(int aTetraminoIndex)
{
	Sprite *tetraminoView = _tetraminosViews[aTetraminoIndex];
	tetraminoView->setVisible(false);
}

bool GameBoardController::getRedrawAvailable()
{
	return _redrawAvailable;
}
