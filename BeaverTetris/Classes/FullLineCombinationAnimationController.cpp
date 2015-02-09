#include "FullLineCombinationAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FullLineCombination.h"
#include "GameBoardViewDataSource.h"
#include "GameBoardController.h"
#include "GameBoard.h"
#include "TetraminoColorsDataSource.h"
#include <string>
#include "GameAnimationActionsConstants.h"
#include "AnimationSynchonizer.h"

using namespace cocos2d;
using namespace std;

FullLineCombinationAnimationController::FullLineCombinationAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer)
{
	FullLineCombination *fullLineCombinationModel = (FullLineCombination*)ServiceLocator::getServiceForKey(fullLineCombinationModelKey);
	fullLineCombinationModel->setDelegate(this);
	_animationSynchonizer = aAnimationSynchonizer;
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_gameBoardViewDataSource = new GameBoardViewDataSource();
	_gameBoardController = aGameBoardController;
	_tetraminoColorsDataSource = new TetraminoColorsDataSource();
}

FullLineCombinationAnimationController::~FullLineCombinationAnimationController(void)
{
}

void FullLineCombinationAnimationController::blowUpLine(int aLineIndex)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = getTetraminosLineExplosionAnimation(aLineIndex);

	FiniteTimeAction *delay = DelayTime::create(tetraminosExplosionDuration);
	FiniteTimeAction *sequence = Sequence::create(tetraminosLineExplosionAnimation, delay, NULL);
	_animationSynchonizer->addAnimationToQueue(sequence);
}

FiniteTimeAction* FullLineCombinationAnimationController::getTetraminosLineExplosionAnimation(int aLineIndex)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = CallFunc::create([this, aLineIndex](){
		vector<Node*> explosions = getExplosionsInLine(aLineIndex);
		addExplosionsToView(explosions);
	});
	return tetraminosLineExplosionAnimation;
}

vector<Node*> FullLineCombinationAnimationController::getExplosionsInLine(int aLineIndex)
{
	vector<Node*> explosions;
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < gameBoardWidth; widthIndex++)
	{
		Node *explosion = getExplosionForOnPositionXY(widthIndex, aLineIndex);
		explosions.push_back(explosion);
	}
	return explosions;
}








Node* FullLineCombinationAnimationController::getExplosionForOnPositionXY(int xPosition, int yPosition)
{
	ParticleSystem *explosion = ParticleExplosion::create();
	explosion->setAutoRemoveOnFinish(true);
	setExplosionColors(explosion);
	setExplosionParticles(explosion);
	setExplosionPositionOnXY(explosion, xPosition, yPosition);
	return explosion;
}

void FullLineCombinationAnimationController::setExplosionColors(ParticleSystem* aExplosion)
{
	aExplosion->setStartColor(Color4F(0.76f, 0.25f, 0.12f, 1.0f));
	aExplosion->setStartColorVar(Color4F(0.0f, 0.0f, 0.0f, 0.0f));
	aExplosion->setEndColor(Color4F(0.0f, 0.0f, 0.0f, 1.0f));
	aExplosion->setEndColorVar(Color4F(0.0f, 0.0f, 0.0f, 0.0f));
	aExplosion->setBlendAdditive(true);
}

void FullLineCombinationAnimationController::setExplosionParticles(ParticleSystem* aExplosion)
{
	aExplosion->setEndSize(0.0f);
	aExplosion->setLife(tetraminosExplosionDuration);
	aExplosion->setLifeVar(0.0f);
	aExplosion->setSpeed(1.5f);
}

void FullLineCombinationAnimationController::setExplosionPositionOnXY(ParticleSystem* aExplosion, int xPosition, int yPosition)
{
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	int firstTetraminoInLineIndex = yPosition * gameBoardWidth;
	int particleIndex = firstTetraminoInLineIndex + xPosition;
	Vec2 particlePosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(particleIndex);
	aExplosion->setPosition(particlePosition);
}

void FullLineCombinationAnimationController::addExplosionsToView(vector<Node*> aExplosions)
{
	vector<Node*>::iterator explosionsIterator;
	for (explosionsIterator = aExplosions.begin(); explosionsIterator != aExplosions.end(); explosionsIterator++)
	{
		Node *explosion = *explosionsIterator;
		this->addChild(explosion);
	}
}

void FullLineCombinationAnimationController::removeTetraminoOnPositionXY(int xPosition, int yPosition)
{
	FiniteTimeAction *actionWithTetraminoView = getRemoveTetraminoAnimationOnPositionXY(xPosition, yPosition);
	_animationSynchonizer->addAnimationToQueue(actionWithTetraminoView);
}

FiniteTimeAction* FullLineCombinationAnimationController::getRemoveTetraminoAnimationOnPositionXY(int xPosition, int yPosition)
{
	GamePositionOnBoard tetraminoPosition;
	tetraminoPosition.xPosition = xPosition;
	tetraminoPosition.yPosition = yPosition;

	removeTetraminoFromBoardOnPosition(tetraminoPosition);
	Node *tetraminoView = getTetraminoViewOnPosition(tetraminoPosition);
	this->addChild(tetraminoView);
	FiniteTimeAction *removeTetraminoAnimation = getRemoveTetraminoAnimationWithView(tetraminoView);
	return removeTetraminoAnimation;
}

void FullLineCombinationAnimationController::removeTetraminoFromBoardOnPosition(GamePositionOnBoard aPosition)
{
	int tetraminoIndex = _gameBoard->getIndexForPosition(aPosition);
	_gameBoardController->cleanTetraminoOnIndex(tetraminoIndex);
}

Node* FullLineCombinationAnimationController::getTetraminoViewOnPosition(GamePositionOnBoard aPosition)
{
	int tetraminoIndex = _gameBoard->getIndexForPosition(aPosition);
	Sprite *tetraminoView = Sprite::create("HelloWorld.png");
	Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(tetraminoIndex);
	tetraminoView->setPosition(tetraminoViewPosition);
	tetraminoView->setScaleX(0.05f);
	tetraminoView->setScaleY(0.08f);
	string tetraminoTexture = _gameBoardViewDataSource->getTetraminoImageForIndex(tetraminoIndex);
	Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(tetraminoTexture);
	tetraminoView->setColor(tetraminoColor);
	return tetraminoView;
}

FiniteTimeAction* FullLineCombinationAnimationController::getRemoveTetraminoAnimationWithView(cocos2d::Node *aView)
{
	FiniteTimeAction *fadeOut = FadeOut::create(tetraminoDisappearDuration);
	FiniteTimeAction *removeViewCallback = CallFunc::create([aView](){aView->removeFromParentAndCleanup(true);});
	Sequence *sequence = Sequence::create(fadeOut, removeViewCallback, NULL);
	FiniteTimeAction *actionWithTetraminoView = TargetedAction::create(aView, sequence);
	return actionWithTetraminoView;
}

void FullLineCombinationAnimationController::setCallback(std::function<void()> aCallback)
{
	FiniteTimeAction *endCallback = CallFunc::create(aCallback);
	_animationSynchonizer->addAnimationToQueue(endCallback);
}

