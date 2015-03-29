#include "AddLineToBoardSpellAnimationController.h"
#include "AnimationSynchonizer.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "AddLineToBoardBottomSpell.h"
#include "TetraminosAppearanceAnimationFactory.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "GameBoardController.h"
#include "TetraminosInGameBoardViewDataSource.h"
#include "GameAnimationActionsConstants.h"
#include "TetraminoViewController.h"

using namespace cocos2d;
using namespace std;

AddLineToBoardSpellAnimationController::AddLineToBoardSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoardController = aGameBoardController;
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_tetraminosInGameBoardViewDataSource = new TetraminosInGameBoardViewDataSource();
	_tetraminosAppearanceAnimationFactory = new TetraminosAppearanceAnimationFactory(aGameBoardController);
	this->addChild(_tetraminosAppearanceAnimationFactory);

	ServiceInterface *service = ServiceLocator::getServiceForKey(addLineToBoardBottomSpellModelKey);
	if (service)
	{
		AddLineToBoardBottomSpell *addLineToBoardBottomSpellModel = (AddLineToBoardBottomSpell*)service;
		addLineToBoardBottomSpellModel->setDelegate(this);
	}
	
}


AddLineToBoardSpellAnimationController::~AddLineToBoardSpellAnimationController(void)
{
	delete _tetraminosInGameBoardViewDataSource;
}

void AddLineToBoardSpellAnimationController::upGameBoard()
{
	Node *gameBoardView = getGameBoardView();
	FiniteTimeAction *animationWithGameBoard = getAnimationWithGameBoardView(gameBoardView);
	_animationSynchonizer->addAnimationToQueue(animationWithGameBoard);
}

Node* AddLineToBoardSpellAnimationController::getGameBoardView()
{
	cleanAllTetraminosFromGameBoardView();
	Node *boardView = Node::create();
	fillViewWithTetraminos(boardView);
	this->addChild(boardView);
	return boardView;
}

void AddLineToBoardSpellAnimationController::cleanAllTetraminosFromGameBoardView()
{
	int tetraminosCount = _tetraminosInGameBoardViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		if (_tetraminosInGameBoardViewDataSource->availableTetraminoOnIndex(tetraminoIndex))
		{
			_gameBoardController->cleanTetraminoOnIndex(tetraminoIndex);
		}
	}
}

void AddLineToBoardSpellAnimationController::fillViewWithTetraminos(Node *aView)
{
	int tetraminosCount = _tetraminosInGameBoardViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{

		if (_tetraminosInGameBoardViewDataSource->availableTetraminoOnIndex(tetraminoIndex))
		{
			addTetraminoOnViewForIndex(aView, tetraminoIndex);
		}
	}
}

void AddLineToBoardSpellAnimationController::addTetraminoOnViewForIndex(Node *aView, int aIndex)
{
	TetraminoViewController *tetraminoView = new TetraminoViewController();
	Vec2 tetraminoViewPosition = _tetraminosInGameBoardViewDataSource->getTetraminoPositionForIndex(aIndex);
	tetraminoView->setPosition(tetraminoViewPosition);
	string tetraminoTexture = _tetraminosInGameBoardViewDataSource->getTetraminoImageForIndex(aIndex);
	int tetraminoTag = getTetraminoViewTagForIndex(aIndex);
	tetraminoView->setTag(tetraminoTag);
	tetraminoView->setTexture(tetraminoTexture);
	setTetraminoLivesCountInViewForIndex(tetraminoView, aIndex);
	aView->addChild(tetraminoView);
}

void AddLineToBoardSpellAnimationController::setTetraminoLivesCountInViewForIndex(TetraminoViewController *aView, int aIndex)
{
	string livesCount = string();
	if (_tetraminosInGameBoardViewDataSource->availableLevesCountOnIndex(aIndex))
	{
		livesCount = _tetraminosInGameBoardViewDataSource->getTetraminoLivesCountForIndex(aIndex);
	}
	aView->setLivesCount(livesCount);
}

int AddLineToBoardSpellAnimationController::getTetraminoViewTagForIndex(int aIndex)
{
	GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(aIndex);
	tetraminoPosition.yPosition = tetraminoPosition.yPosition + 1;
	int tetraminoTag = _gameBoard->getIndexForPosition(tetraminoPosition);
	return tetraminoTag;
}

FiniteTimeAction* AddLineToBoardSpellAnimationController::getAnimationWithGameBoardView(Node *aView)
{
	FiniteTimeAction *moveBoard = getMoveBoardAnimationWithView(aView);
	function<void(Node*)> callbackFunction = getAnimationEndCallback();
	FiniteTimeAction *callback = CallFuncN::create(callbackFunction);
	FiniteTimeAction *sequence = Sequence::create(moveBoard,callback, NULL);
	FiniteTimeAction *animationWithGameBoard = TargetedAction::create(aView,sequence);
	return animationWithGameBoard;
}

FiniteTimeAction* AddLineToBoardSpellAnimationController::getMoveBoardAnimationWithView(Node *aView)
{
	int gameBoardWidth =  _gameBoard->getGameBoardWidth();
	int finalBoardPositionIndex = gameBoardWidth;
	Vec2 finalBoardPosition = _tetraminosInGameBoardViewDataSource->getTetraminoPositionForIndex(finalBoardPositionIndex);
	Vec2 currentBoardPosition = aView->getPosition();
	float yDifference = finalBoardPosition.y - currentBoardPosition.y;
	float animationDuration = yDifference * fallActionDurationPerTetramino;
	FiniteTimeAction *moveBoard = MoveTo::create(animationDuration, finalBoardPosition);
	return moveBoard;
}

function<void(Node*)> AddLineToBoardSpellAnimationController::getAnimationEndCallback()
{
	function<void(Node*)> callback = [this](Node *sender){
		cleanBoardViewChildren(sender);
		sender->removeFromParentAndCleanup(true);
	};
	return callback;
}

void AddLineToBoardSpellAnimationController::cleanBoardViewChildren(Node *aView)
{
	Vector<Node*> children = aView->getChildren();
	Vector<Node*>::iterator childrenIterator;
	for (childrenIterator = children.begin(); childrenIterator != children.end(); childrenIterator++)
	{
		Node *child = *childrenIterator;
		TetraminoViewController *view = (TetraminoViewController*)child;
		int childTag = child->getTag();
		string childName = view->getTextureName();
		_gameBoardController->drawTetraminoTextureOnIndex(childName, childTag);
	}
}

void AddLineToBoardSpellAnimationController::addLineToGameBoard()
{
	vector<GamePositionOnBoard> linePositions = getBottomLinePositions();
	addAnimationWithPositions(linePositions);
}

vector<GamePositionOnBoard> AddLineToBoardSpellAnimationController::getBottomLinePositions()
{
	vector<GamePositionOnBoard> bottomLinePositions;
	int boardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < boardWidth; widthIndex++)
	{
		setPositionWithIndexInCollection(widthIndex, bottomLinePositions);
	}
	return bottomLinePositions;
}

void AddLineToBoardSpellAnimationController::setPositionWithIndexInCollection(int aWidthIndex, vector<GamePositionOnBoard> &aPositions)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aWidthIndex, 0);
	if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty)
	{
		GamePositionOnBoard position;
		position.xPosition = aWidthIndex;
		position.yPosition = 0;
		aPositions.push_back(position);
	}
}

void AddLineToBoardSpellAnimationController::addAnimationWithPositions(vector<GamePositionOnBoard> &aPositions)
{
	vector<GamePositionOnBoard>::iterator positionsIterator;
	for (positionsIterator = aPositions.begin(); positionsIterator != aPositions.end(); positionsIterator++)
	{
		GamePositionOnBoard position = *positionsIterator;
		FiniteTimeAction *animationWithTetraminoView = _tetraminosAppearanceAnimationFactory->getAnimationWithTetraminoPosition(position);
		_animationSynchonizer->addAnimationToQueue(animationWithTetraminoView);
	}
}