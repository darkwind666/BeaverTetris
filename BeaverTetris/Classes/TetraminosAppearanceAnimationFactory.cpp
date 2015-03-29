#include "TetraminosAppearanceAnimationFactory.h"
#include "GameBoardController.h"
#include "GameBoardViewDataSource.h"
#include "GameBoard.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameAnimationActionsConstants.h"
#include "Tetramino.h"
#include "StringsSupporter.h"
#include "TetraminoViewController.h"

using namespace cocos2d;

TetraminosAppearanceAnimationFactory::TetraminosAppearanceAnimationFactory(GameBoardController *aGameBoardController)
{
	_gameBoardController = aGameBoardController;
	_gameBoardViewDataSource = new GameBoardViewDataSource();
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}


TetraminosAppearanceAnimationFactory::~TetraminosAppearanceAnimationFactory(void)
{
}

FiniteTimeAction* TetraminosAppearanceAnimationFactory::getAnimationWithTetraminoPosition(GamePositionOnBoard aPosition)
{
	Node *tetraminoView = getTetraminoViewFromPosition(aPosition);
	FiniteTimeAction *animationWithTetraminoView = getAnimationWithView(tetraminoView);
	return animationWithTetraminoView;
}

Node* TetraminosAppearanceAnimationFactory::getTetraminoViewFromPosition(GamePositionOnBoard aPosition)
{
	TetraminoViewController *tetraminoView = new TetraminoViewController();
	this->addChild(tetraminoView);
	int positionIndex = _gameBoard->getIndexForPosition(aPosition);
	string tetraminoTexture = _gameBoardViewDataSource->getTetraminoImageForIndex(positionIndex);
	Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(positionIndex);
	tetraminoView->setTag(positionIndex);
	tetraminoView->setScale(0.0f);
	tetraminoView->setOpacity(0.0f);
	tetraminoView->setTexture(tetraminoTexture);
	tetraminoView->setPosition(tetraminoViewPosition);
	setLivesCountInViewWithTetraminoPosition(tetraminoView, aPosition);
	return tetraminoView;
}

void TetraminosAppearanceAnimationFactory::setLivesCountInViewWithTetraminoPosition(TetraminoViewController *aView, GamePositionOnBoard aPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
	string lives = string();
	TetraminoType type = tetraminoInBoard->getTetraminoType();
	int livesCount = tetraminoInBoard->getTetraminoLivesCount();
	if (type > kTetraminoEmpty && type < kTetraminoBossQueen && livesCount > 1)
	{
		lives = StringsSupporter::getStringFromNumber(livesCount);
	}
	aView->setLivesCount(lives);
}

FiniteTimeAction* TetraminosAppearanceAnimationFactory::getAnimationWithView(Node *aView)
{
	FiniteTimeAction *viewAnimation = getViewAnimation();
	FiniteTimeAction *callback = getAnimationCallback();
	FiniteTimeAction *sequence = Sequence::create(viewAnimation, callback, NULL);
	FiniteTimeAction *animationWithTetramino = TargetedAction::create(aView, sequence);
	return animationWithTetramino;
}

FiniteTimeAction* TetraminosAppearanceAnimationFactory::getViewAnimation()
{
	FiniteTimeAction *scale = ScaleTo::create(tetraminoAppearDuration, 1.0f);
	FiniteTimeAction *appear = FadeIn::create(tetraminoAppearDuration);
	FiniteTimeAction *spawn = Spawn::create(scale, appear, NULL);
	return spawn;
}

FiniteTimeAction* TetraminosAppearanceAnimationFactory::getAnimationCallback()
{
	FiniteTimeAction *callback = CallFuncN::create([this](Node *sender){
		TetraminoViewController *view = (TetraminoViewController*)sender;
		int index = sender->getTag();
		string childName = view->getTextureName();
		_gameBoardController->drawTetraminoTextureOnIndex(childName, index);
		sender->removeFromParentAndCleanup(true);
	});
	return callback;
}