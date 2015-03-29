#include "TetraminoExplosionFactory.h"
#include "GameAnimationActionsConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "GameBoardViewDataSource.h"
#include "GameBoardController.h"
#include "TetraminoViewController.h"

using namespace cocos2d;
using namespace std;

TetraminoExplosionFactory::TetraminoExplosionFactory(GameBoardController *aGameBoardController)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_gameBoardViewDataSource = new GameBoardViewDataSource();
	_gameBoardController = aGameBoardController;
}


TetraminoExplosionFactory::~TetraminoExplosionFactory(void)
{
}


FiniteTimeAction* TetraminoExplosionFactory::getTetraminosExplosionsAnimationWithPositions(vector<GamePositionOnBoard> aPositions)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = CallFunc::create([this, aPositions](){
		vector<Node*> explosions = getExplosionsFromPositions(aPositions);
		addExplosionsToView(explosions);
	});
	FiniteTimeAction *delay = DelayTime::create(tetraminosExplosionDuration);
	FiniteTimeAction *sequence = Sequence::create(tetraminosLineExplosionAnimation, delay, NULL);
	FiniteTimeAction *blowUpAnimation = TargetedAction::create(this, sequence);
	return blowUpAnimation;
}

vector<Node*> TetraminoExplosionFactory::getExplosionsFromPositions(vector<GamePositionOnBoard> tetraminosPositions)
{
	vector<Node*> explosions;
	vector<GamePositionOnBoard>::iterator positionIterator;
	for (positionIterator = tetraminosPositions.begin(); positionIterator != tetraminosPositions.end(); positionIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *positionIterator;
		Node *explosion = getExplosionForOnPositionXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		explosions.push_back(explosion);
	}
	return explosions;
}

Node* TetraminoExplosionFactory::getExplosionForOnPositionXY(int xPosition, int yPosition)
{
	ParticleSystem *explosion = ParticleExplosion::create();
	explosion->setAutoRemoveOnFinish(true);
	setExplosionColors(explosion);
	setExplosionParticles(explosion);
	setExplosionPositionOnXY(explosion, xPosition, yPosition);
	return explosion;
}

void TetraminoExplosionFactory::setExplosionColors(ParticleSystem* aExplosion)
{
	aExplosion->setStartColor(Color4F(0.76f, 0.25f, 0.12f, 1.0f));
	aExplosion->setStartColorVar(Color4F(0.0f, 0.0f, 0.0f, 0.0f));
	aExplosion->setEndColor(Color4F(0.0f, 0.0f, 0.0f, 1.0f));
	aExplosion->setEndColorVar(Color4F(0.0f, 0.0f, 0.0f, 0.0f));
	aExplosion->setBlendAdditive(true);
}

void TetraminoExplosionFactory::setExplosionParticles(ParticleSystem* aExplosion)
{
	aExplosion->setEndSize(0.0f);
	aExplosion->setLife(tetraminosExplosionDuration);
	aExplosion->setLifeVar(0.0f);
	aExplosion->setSpeed(1.5f);
}

void TetraminoExplosionFactory::setExplosionPositionOnXY(ParticleSystem* aExplosion, int xPosition, int yPosition)
{
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	int firstTetraminoInLineIndex = yPosition * gameBoardWidth;
	int particleIndex = firstTetraminoInLineIndex + xPosition;
	Vec2 particlePosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(particleIndex);
	aExplosion->setPosition(particlePosition);
}

void TetraminoExplosionFactory::addExplosionsToView(vector<Node*> aExplosions)
{
	vector<Node*>::iterator explosionsIterator;
	for (explosionsIterator = aExplosions.begin(); explosionsIterator != aExplosions.end(); explosionsIterator++)
	{
		Node *explosion = *explosionsIterator;
		this->addChild(explosion);
	}
}

FiniteTimeAction* TetraminoExplosionFactory::getRemoveTetraminoActionOnPositionXY(int xPosition, int yPosition)
{
	FiniteTimeAction *actionWithTetraminoView = getRemoveTetraminoAnimationOnPositionXY(xPosition, yPosition);
	return actionWithTetraminoView;
}

FiniteTimeAction* TetraminoExplosionFactory::getRemoveTetraminoAnimationOnPositionXY(int xPosition, int yPosition)
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

void TetraminoExplosionFactory::removeTetraminoFromBoardOnPosition(GamePositionOnBoard aPosition)
{
	int tetraminoIndex = _gameBoard->getIndexForPosition(aPosition);
	_gameBoardController->cleanTetraminoOnIndex(tetraminoIndex);
}

Node* TetraminoExplosionFactory::getTetraminoViewOnPosition(GamePositionOnBoard aPosition)
{
	TetraminoViewController *tetraminoView = new TetraminoViewController();
	int tetraminoIndex = _gameBoard->getIndexForPosition(aPosition);
	Vec2 tetraminoViewPosition = _gameBoardViewDataSource->getTetraminoPositionForIndex(tetraminoIndex);
	tetraminoView->setPosition(tetraminoViewPosition);
	string tetraminoTexture = _gameBoardViewDataSource->getTetraminoImageForIndex(tetraminoIndex);
	tetraminoView->setTexture(tetraminoTexture);
	return tetraminoView;
}

FiniteTimeAction* TetraminoExplosionFactory::getRemoveTetraminoAnimationWithView(Node *aView)
{
	FiniteTimeAction *fadeOut = FadeOut::create(tetraminoDisappearDuration);
	FiniteTimeAction *removeViewCallback = CallFunc::create([aView](){aView->removeFromParentAndCleanup(true);});
	Sequence *sequence = Sequence::create(fadeOut, removeViewCallback, NULL);
	FiniteTimeAction *actionWithTetraminoView = TargetedAction::create(aView, sequence);
	return actionWithTetraminoView;
}

FiniteTimeAction* TetraminoExplosionFactory::getCallbackAction(std::function<void()> aCallback)
{
	FiniteTimeAction *endCallback = CallFunc::create(aCallback);
	return endCallback;
}

