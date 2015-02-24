#include "CohesionSpellAnimationController.h"
#include "GameBoardController.h"
#include "AnimationSynchonizer.h"
#include "GameBoardViewDataSource.h"
#include "GameBoard.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "TetraminoColorsDataSource.h"
#include "CohesionSpell.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

CohesionSpellAnimationController::CohesionSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoardController = aGameBoardController;
	_gameBoardViewDataSource = new GameBoardViewDataSource();
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_tetraminoColorsDataSource = new TetraminoColorsDataSource();

	CohesionSpell *cohesionSpellModel = (CohesionSpell*)ServiceLocator::getServiceForKey(cohesionSpellModelKey);
	cohesionSpellModel->setDelegate(this);

}


CohesionSpellAnimationController::~CohesionSpellAnimationController(void)
{
}

void CohesionSpellAnimationController::makeTetraminoOnPosition(GamePositionOnBoard aPosition)
{
	Node *tetraminoView = getTetraminoViewFromPosition(aPosition);
	FiniteTimeAction *animationWithTetraminoView = getAnimationWithView(tetraminoView);
	_animationSynchonizer->addAnimationToQueue(animationWithTetraminoView);
}

Node* CohesionSpellAnimationController::getTetraminoViewFromPosition(GamePositionOnBoard aPosition)
{
	Sprite *tetraminoView = Sprite::create("HelloWorld.png");
	this->addChild(tetraminoView);
	int positionIndex = _gameBoard->getIndexForPosition(aPosition);
	setViewColorAndNameAndPositionWithIndex(tetraminoView, positionIndex);
	tetraminoView->setTag(positionIndex);
	tetraminoView->setScale(0.0f);
	tetraminoView->setOpacity(0.0f);
	return tetraminoView;
}

void CohesionSpellAnimationController::setViewColorAndNameAndPositionWithIndex(Node *aView, int aIndex)
{
	string tetraminoTexture = _gameBoardViewDataSource->getTetraminoImageForIndex(aIndex);
	Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(tetraminoTexture);
	Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(aIndex);
	aView->setPosition(tetraminoViewPosition);
	aView->setColor(tetraminoColor);
	aView->setName(tetraminoTexture);
}

FiniteTimeAction* CohesionSpellAnimationController::getAnimationWithView(Node *aView)
{
	FiniteTimeAction *viewAnimation = getViewAnimation();
	FiniteTimeAction *callback = getAnimationCallback();
	FiniteTimeAction *sequence = Sequence::create(viewAnimation, callback, NULL);
	FiniteTimeAction *animationWithTetramino = TargetedAction::create(aView, sequence);
	return animationWithTetramino;
}

FiniteTimeAction* CohesionSpellAnimationController::getViewAnimation()
{
	FiniteTimeAction *scale = ScaleTo::create(tetraminoAppearDuration, 0.05f, 0.08f);
	FiniteTimeAction *appear = FadeIn::create(tetraminoAppearDuration);
	FiniteTimeAction *spawn = Spawn::create(scale, appear, NULL);
	return spawn;
}

FiniteTimeAction* CohesionSpellAnimationController::getAnimationCallback()
{
	FiniteTimeAction *callback = CallFuncN::create([this](Node *sender){
		int index = sender->getTag();
		string childName = sender->getName();
		_gameBoardController->drawTetraminoTextureOnIndex(childName, index);
		sender->removeFromParentAndCleanup(true);
	});
	return callback;
}