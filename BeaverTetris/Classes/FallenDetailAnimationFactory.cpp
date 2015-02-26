#include "FallenDetailAnimationFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "DetailViewDataSource.h"
#include "TetraminoColorsDataSource.h"
#include "TetraminoDetail.h"
#include "GameBoard.h"
#include "GameAnimationActionsConstants.h"
#include "FuctionsTypedefs.h"
#include "GameBoardController.h"

using namespace cocos2d;

FallenDetailAnimationFactory::FallenDetailAnimationFactory(DetailViewDataSource *aDataSource, GameBoardController *aGameBoardController)
{
	_gameBoardController = aGameBoardController;
	_dataSource = aDataSource;
	_tetraminoColorsDataSource = new TetraminoColorsDataSource();
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}


FallenDetailAnimationFactory::~FallenDetailAnimationFactory(void)
{
	delete _dataSource;
}

void FallenDetailAnimationFactory::cleanDetailViewOnBoard()
{
	DetailCleaner cleanerCallback = [this](GamePositionOnBoard aPosition){
		int positionIndex = _gameBoard->getIndexForPosition(aPosition);
		_gameBoardController->cleanTetraminoOnIndex(positionIndex);
	};
	_dataSource->cleanDetailWithCleanerCallback(cleanerCallback);
}

Node* FallenDetailAnimationFactory::getCurrentDetailView()
{
	Node *follenDetail = Node::create();
	fillDetailWithTetraminos(follenDetail);
	Vec2 follenDetailPosition = _dataSource->getDetailPositionOnView();
	follenDetail->setPosition(follenDetailPosition);
	return follenDetail;
}

void FallenDetailAnimationFactory::fillDetailWithTetraminos(Node* aDetailView)
{
	int tetraminosCount = _dataSource->getTetraminosCount();
	for (int tetraminoIndex = 0; tetraminoIndex < tetraminosCount; tetraminoIndex++)
	{
		if (_dataSource->availableTetraminoOnIndex(tetraminoIndex))
		{
			Node *tetraminoView = getCurrentDetailTetraminoViewOnIndex(tetraminoIndex);
			aDetailView->addChild(tetraminoView);
		}
	}
}

Node* FallenDetailAnimationFactory::getCurrentDetailTetraminoViewOnIndex(int aIndex)
{
	Sprite *tetraminoView = Sprite::create("HelloWorld.png");
	Vec2 tetraminoViewPosition = _dataSource->getTetraminoPositionForIndex(aIndex);
	tetraminoView->setPosition(tetraminoViewPosition);
	tetraminoView->setScaleX(0.05f);
	tetraminoView->setScaleY(0.08f);
	string tetraminoTexture = _dataSource->getTetraminoImageForIndex(aIndex);
	Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(tetraminoTexture);
	tetraminoView->setColor(tetraminoColor);
	int tetraminoTag = getTetraminoTagForIndex(aIndex);
	tetraminoView->setTag(tetraminoTag);
	tetraminoView->setName(tetraminoTexture);
	return tetraminoView;
}

int FallenDetailAnimationFactory::getTetraminoTagForIndex(int aIndex)
{
	GamePositionOnBoard positionInDetail = _dataSource->getTetraminoPositionInBoardForIndex(aIndex);
	int tetraminoTag = _gameBoard->getIndexForPosition(positionInDetail);
	return tetraminoTag;
}

FiniteTimeAction* FallenDetailAnimationFactory::getDetailAnimationWithFinalPosition(GamePositionOnBoard aFinalPosition)
{
	Vec2 finalDetailPosition = getPositionOnViewWithTetraminoOffset(aFinalPosition);
	float animationDuration = getAnimationDurationWithFinalPosition(aFinalPosition);
	FiniteTimeAction *moveDetail = MoveTo::create(animationDuration, finalDetailPosition);
	function<void(Node*)> callbackFunction = getAnimationEndCallbackWithFinalPosition(aFinalPosition);
	FiniteTimeAction *callback = CallFuncN::create(callbackFunction);
	FiniteTimeAction *sequence = Sequence::create(moveDetail,callback, NULL);
	return sequence;
}

Vec2 FallenDetailAnimationFactory::getPositionOnViewWithTetraminoOffset(GamePositionOnBoard aPosition)
{
	Vec2 tetraminosOffset = _dataSource->getTetraminosViewOffset();
	Vec2 position = Vec2(aPosition.xPosition * tetraminosOffset.x, aPosition.yPosition * tetraminosOffset.y);
	return position;
}

float FallenDetailAnimationFactory::getAnimationDurationWithFinalPosition(GamePositionOnBoard aFinalPosition)
{
	Vec2 currentDetailPosition = _dataSource->getDetailPositionOnView();
	Vec2 finalDetailPosition = _dataSource->getPositionOnView(aFinalPosition);
	float yDifference = currentDetailPosition.y - finalDetailPosition.y;
	float animationDuration = yDifference * fallActionDurationPerTetramino;
	return animationDuration;
}

function<void(Node*)>  FallenDetailAnimationFactory::getAnimationEndCallbackWithFinalPosition(GamePositionOnBoard aFinalPosition)
{
	GamePositionOnBoard detailPositionDifference = getPositionDifferenceWithFinalPosition(aFinalPosition);
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	GameBoardController *gameBoardController = _gameBoardController;

	function<void(Node*)> callback = [gameBoardController, detailPositionDifference, gameBoardWidth](Node *sender){

		Vector<Node*> children = sender->getChildren();
		Vector<Node*>::iterator childrenIterator;
		for (childrenIterator = children.begin(); childrenIterator != children.end(); childrenIterator++)
		{
			Node *child = *childrenIterator;
			int childTag = child->getTag();
			int index = childTag + (detailPositionDifference.yPosition * gameBoardWidth) + detailPositionDifference.xPosition;
			string childName = child->getName();
			gameBoardController->drawTetraminoTextureOnIndex(childName, index);
		}
		sender->removeFromParentAndCleanup(true);

	};
	return callback;
}

GamePositionOnBoard FallenDetailAnimationFactory::getPositionDifferenceWithFinalPosition(GamePositionOnBoard aFinalPosition)
{
	GamePositionOnBoard currentDetailPosition = _dataSource->getDetailPositionOnBoard();
	GamePositionOnBoard detailPositionDifference;
	detailPositionDifference.xPosition = aFinalPosition.xPosition - currentDetailPosition.xPosition;
	detailPositionDifference.yPosition = aFinalPosition.yPosition - currentDetailPosition.yPosition;
	return detailPositionDifference;
}