#include "AddLineToBoardSpellAnimationController.h"
#include "AnimationSynchonizer.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "AddLineToBoardBottomSpell.h"
#include "TetraminosAppearanceAnimationFactory.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "GameBoardController.h"
#include "GameBoardViewDataSource.h"
#include "TetraminoColorsDataSource.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;
using namespace std;

AddLineToBoardSpellAnimationController::AddLineToBoardSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoardController = aGameBoardController;
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_tetraminoColorsDataSource = new TetraminoColorsDataSource();
	_gameBoardViewDataSource = new GameBoardViewDataSource();
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
	delete _gameBoardViewDataSource;
}

void AddLineToBoardSpellAnimationController::upGameBoard()
{
	Node *gameBoardView = getGameBoardView();
	FiniteTimeAction *animationWithGameBoard = getAnimationWithGameBoardView(gameBoardView);
	_animationSynchonizer->addAnimationToQueue(animationWithGameBoard);
}

Node* AddLineToBoardSpellAnimationController::getGameBoardView()
{
	cleanAllTetraminosFromView();
	Node *boardView = Node::create();
	fillViewWithTetraminos(boardView);
	this->addChild(boardView);
	return boardView;
}

void AddLineToBoardSpellAnimationController::fillViewWithTetraminos(Node *aView)
{
	int tetraminosCount = _gameBoardViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		if (_gameBoardViewDataSource->availableTetraminoOnIndex(tetraminoIndex))
		{
			Sprite *tetraminoView = Sprite::create("HelloWorld.png");
			Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(tetraminoIndex);
			tetraminoView->setPosition(tetraminoViewPosition);
			tetraminoView->setScaleX(0.05f);
			tetraminoView->setScaleY(0.08f);
			string tetraminoTexture = _gameBoardViewDataSource->getTetraminoImageForIndex(tetraminoIndex);
			Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(tetraminoTexture);
			tetraminoView->setColor(tetraminoColor);

			GamePositionOnBoard tetraminoPosition = _gameBoard->getPositionForIndex(tetraminoIndex);
			tetraminoPosition.yPosition = tetraminoPosition.yPosition + 1;

			int tetraminoTag = _gameBoard->getIndexForPosition(tetraminoPosition);
			tetraminoView->setTag(tetraminoTag);
			tetraminoView->setName(tetraminoTexture);
			aView->addChild(tetraminoView);
		}
	}
}

void AddLineToBoardSpellAnimationController::cleanAllTetraminosFromView()
{
	int tetraminosCount = _gameBoardViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		_gameBoardController->cleanTetraminoOnIndex(tetraminoIndex);
	}
}

FiniteTimeAction* AddLineToBoardSpellAnimationController::getAnimationWithGameBoardView(Node *aView)
{
	int gameBoardWidth =  _gameBoard->getGameBoardWidth();
	int finalBoardPositionIndex = gameBoardWidth;
	Vec2 finalBoardPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(finalBoardPositionIndex);
	Vec2 currentBoardPosition = aView->getPosition();
	float yDifference = finalBoardPosition.y - currentBoardPosition.y;
	float animationDuration = yDifference * fallActionDurationPerTetramino;

	FiniteTimeAction *moveDetail = MoveTo::create(animationDuration, finalBoardPosition);
	function<void(Node*)> callbackFunction = getAnimationEndCallback();
	FiniteTimeAction *callback = CallFuncN::create(callbackFunction);
	FiniteTimeAction *sequence = Sequence::create(moveDetail,callback, NULL);
	FiniteTimeAction *animationWithGameBoard = TargetedAction::create(aView,sequence);
	return animationWithGameBoard;
}

function<void(Node*)> AddLineToBoardSpellAnimationController::getAnimationEndCallback()
{
	function<void(Node*)> callback = [this](Node *sender){
		Vector<Node*> children = sender->getChildren();
		Vector<Node*>::iterator childrenIterator;
		for (childrenIterator = children.begin(); childrenIterator != children.end(); childrenIterator++)
		{
			Node *child = *childrenIterator;
			int childTag = child->getTag();
			string childName = child->getName();
			_gameBoardController->drawTetraminoTextureOnIndex(childName, childTag);
		}
		sender->removeFromParentAndCleanup(true);
	};
	return callback;
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