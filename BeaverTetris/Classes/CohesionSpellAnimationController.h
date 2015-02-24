#pragma once

#include "cocos2d.h"
#include "CohesionSpellDelegate.h"
#include "GameBoardViewDataSource.h"

class GameBoardController;
class AnimationSynchonizer;
class GameBoardViewDataSource;
class GameBoard;
class TetraminoColorsDataSource;

class CohesionSpellAnimationController : public CohesionSpellDelegate, public cocos2d::Node
{
public:
	CohesionSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~CohesionSpellAnimationController(void);

	virtual void makeTetraminoOnPosition(GamePositionOnBoard aPosition);

private:

	AnimationSynchonizer *_animationSynchonizer;
	GameBoardController *_gameBoardController;
	GameBoardViewDataSource *_gameBoardViewDataSource;
	GameBoard *_gameBoard;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;

	cocos2d::Node* getTetraminoViewFromPosition(GamePositionOnBoard aPosition);
	void setViewColorAndNameAndPositionWithIndex(cocos2d::Node *aView, int aIndex);
	cocos2d::FiniteTimeAction* getAnimationWithView(cocos2d::Node *aView);
	cocos2d::FiniteTimeAction* getViewAnimation();
	cocos2d::FiniteTimeAction* getAnimationCallback();

};

