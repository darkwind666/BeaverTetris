#include "CurrentDetailAnimationControler.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "CurrentDetailViewDataSource.h"
#include "TetraminoColorsDataSource.h"
#include "GameBoardController.h"
#include "TetraminoDetail.h"
#include "GameTimeStepController.h"
#include "CurrentDetailController.h"
#include "GameBoard.h"

const float fallActionDurationPerTetramino = 0.015f;

using namespace cocos2d;

CurrentDetailAnimationControler::CurrentDetailAnimationControler(GameBoardController *aGameBoardController)
{
	_gameBoardController = aGameBoardController;
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_currentDetailViewDataSource = new CurrentDetailViewDataSource();
	_tetraminoColorsDataSource = new TetraminoColorsDataSource();
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);

	CurrentDetailController *currentDetailController = (CurrentDetailController*)ServiceLocator::getServiceForKey(currentDetailControllerKey);
	currentDetailController->setDelegate(this);
}


CurrentDetailAnimationControler::~CurrentDetailAnimationControler(void)
{
}

void CurrentDetailAnimationControler::throwCurrentDetailOnPosition(GamePositionOnBoard aPosition)
{
	_gameTimeStepController->setUpdateAvailable(false);
	cleanDetailViewOnBoard();
	Node *follenDetail = getCurrentDetailView();
	Action *moveDetail = getDetailAnimationWithFinalPosition(aPosition);
	follenDetail->runAction(moveDetail);
}

void CurrentDetailAnimationControler::cleanDetailViewOnBoard()
{
	TetraminoDetail *currentDetail =  _currentDetailDataSource->getCurrentDetail();
	int detailWidth = currentDetail->getDetailWidth();
	int detailHeight = currentDetail->getDetailHeight();

	for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
	{
		for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
		{
			cleanTetraminoForXY(widthIndex, heightIndex);
		}
	}
}

void CurrentDetailAnimationControler::cleanTetraminoForXY(int xPosition, int yPosition)
{
	TetraminoDetail *currentDetail =  _currentDetailDataSource->getCurrentDetail();
	GamePositionOnBoard positionInDetail;
	positionInDetail.xPosition = xPosition;
	positionInDetail.yPosition = yPosition;
	GamePositionOnBoard absolutePosition = currentDetail->convertPositionInDetailToAbsolutePosition(positionInDetail);
	int positionIndex = _gameBoard->getIndexForPosition(absolutePosition);
	_gameBoardController->cleanTetraminoOnIndex(positionIndex);
}

Node* CurrentDetailAnimationControler::getCurrentDetailView()
{
	Node *follenDetail = Node::create();
	fillDetailWithTetraminos(follenDetail);
	Vec2 follenDetailPosition = getCurrentDetailPositionOnView();
	follenDetail->setPosition(follenDetailPosition);
	this->addChild(follenDetail);
	return follenDetail;
}

void CurrentDetailAnimationControler::fillDetailWithTetraminos(Node* aDetailView)
{
	int tetraminosCount = _currentDetailViewDataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		if (_currentDetailViewDataSource->availableTetraminoOnIndex(tetraminoIndex))
		{
			Node *tetraminoView = getCurrentDetailTetraminoViewOnIndex(tetraminoIndex);
			aDetailView->addChild(tetraminoView);
		}
	}
}

Node* CurrentDetailAnimationControler::getCurrentDetailTetraminoViewOnIndex(int aIndex)
{
	Sprite *tetraminoView = Sprite::create("HelloWorld.png");
	Vec2 tetraminoViewPosition = _currentDetailViewDataSource->getTetraminoPositionForIndex(aIndex);
	tetraminoView->setPosition(tetraminoViewPosition);
	tetraminoView->setScaleX(0.05f);
	tetraminoView->setScaleY(0.08f);
	string tetraminoTexture = _currentDetailViewDataSource->getTetraminoImageForIndex(aIndex);
	Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(tetraminoTexture);
	tetraminoView->setColor(tetraminoColor);
	return tetraminoView;
}

Vec2 CurrentDetailAnimationControler::getCurrentDetailPositionOnView()
{
	GamePositionOnBoard currentDetailPosition = _currentDetailDataSource->getCurrentDetailPosition();
	int positionIndex = _gameBoard->getIndexForPosition(currentDetailPosition);
	Vec2 follenDetailPosition = getPositionOnViewWithTetraminoOffset(currentDetailPosition);
	return follenDetailPosition;
}

Vec2 CurrentDetailAnimationControler::getPositionOnViewWithTetraminoOffset(GamePositionOnBoard aPosition)
{
	Vec2 tetraminosOffset = _currentDetailViewDataSource->getTetraminosViewOffset();
	Vec2 position = Vec2(aPosition.xPosition * tetraminosOffset.x, aPosition.yPosition * tetraminosOffset.y);
	return position;
}

Action* CurrentDetailAnimationControler::getDetailAnimationWithFinalPosition(GamePositionOnBoard aFinalPosition)
{
	Vec2 finalDetailPosition = getPositionOnViewWithTetraminoOffset(aFinalPosition);
	float animationDuration = getAnimationDurationWithFinalPosition(aFinalPosition);
	FiniteTimeAction *moveDetail = MoveTo::create(animationDuration, finalDetailPosition);
	FiniteTimeAction *callback = CallFuncN::create(CC_CALLBACK_1(CurrentDetailAnimationControler::animationEndCallback, this));
	Action *sequence = Sequence::create(moveDetail,callback, NULL);
	return sequence;
}

float CurrentDetailAnimationControler::getAnimationDurationWithFinalPosition(GamePositionOnBoard aFinalPosition)
{
	GamePositionOnBoard currentDetailPosition = _currentDetailDataSource->getCurrentDetailPosition();
	int yDifference = currentDetailPosition.yPosition - aFinalPosition.yPosition;
	float animationDuration = yDifference * fallActionDurationPerTetramino;
	return animationDuration;
}

void CurrentDetailAnimationControler::animationEndCallback(Node *sender)
{
	_gameTimeStepController->setUpdateAvailable(true);
	this->removeChild(sender);
}