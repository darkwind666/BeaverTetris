#pragma once

#include "cocos2d.h"
#include "GameStructures.h"

class GameBoardController;
class GameBoardViewDataSource;
class GameBoard;
class TetraminoColorsDataSource;

class TetraminosAppearanceAnimationFactory : public cocos2d::Node
{
public:
	TetraminosAppearanceAnimationFactory(GameBoardController *aGameBoardController);
	~TetraminosAppearanceAnimationFactory(void);

	cocos2d::FiniteTimeAction* getAnimationWithTetraminoPosition(GamePositionOnBoard aPosition);

private:

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

