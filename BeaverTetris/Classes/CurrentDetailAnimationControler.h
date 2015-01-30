#pragma once

#include "CurrentDetailControllerDelegate.h"
#include "cocos2d.h"

class GameBoardController;
class CurrentDetailDataSource;
class CurrentDetailViewDataSource;
class TetraminoColorsDataSource;
class GameTimeStepController;
class GameBoard;

class CurrentDetailAnimationControler : public cocos2d::Node, public CurrentDetailControllerDelegate
{
public:
	CurrentDetailAnimationControler(GameBoardController *aGameBoardController);
	~CurrentDetailAnimationControler(void);

	virtual void throwCurrentDetailOnPosition(GamePositionOnBoard aPosition);

private:

	GameBoardController *_gameBoardController;
	GameTimeStepController *_gameTimeStepController;
	CurrentDetailDataSource *_currentDetailDataSource;
	CurrentDetailViewDataSource *_currentDetailViewDataSource;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;
	GameBoard *_gameBoard;

	void cleanDetailViewOnBoard();
	void cleanTetraminoForXY(int xPosition, int yPosition);

	cocos2d::Node* getCurrentDetailView();
	void fillDetailWithTetraminos(cocos2d::Node* aDetailView);
	cocos2d::Vec2 getCurrentDetailPositionOnView();
	cocos2d::Vec2 getPositionOnViewWithTetraminoOffset(GamePositionOnBoard aPosition);
	cocos2d::Node* getCurrentDetailTetraminoViewOnIndex(int aIndex);

	cocos2d::Action* getDetailAnimationWithFinalPosition(GamePositionOnBoard aFinalPosition);
	float getAnimationDurationWithFinalPosition(GamePositionOnBoard aFinalPosition);

	void animationEndCallback(cocos2d::Node *sender);

};

