#pragma once

#include "cocos2d.h"
#include "GameStructures.h"

class DetailViewDataSource;
class TetraminoColorsDataSource;
class GameBoardController;
class GameBoard;

class FallenDetailAnimationFactory
{
public:
	FallenDetailAnimationFactory(DetailViewDataSource *aDataSource, GameBoardController *aGameBoardController);
	~FallenDetailAnimationFactory(void);

	void cleanDetailViewOnBoard();
	cocos2d::Node* getCurrentDetailView();
	cocos2d::FiniteTimeAction* getDetailAnimationWithFinalPosition(GamePositionOnBoard aPosition);

private:

	GameBoardController *_gameBoardController;
	DetailViewDataSource *_dataSource;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;
	GameBoard *_gameBoard;

	void fillDetailWithTetraminos(cocos2d::Node* aDetailView);
	cocos2d::Vec2 getPositionOnViewWithTetraminoOffset(GamePositionOnBoard aPosition);
	cocos2d::Node* getCurrentDetailTetraminoViewOnIndex(int aIndex);
	int getTetraminoTagForIndex(int aIndex);
	float getAnimationDurationWithFinalPosition(GamePositionOnBoard aFinalPosition);
	
	void animationEndCallback(cocos2d::Node *sender);

};

