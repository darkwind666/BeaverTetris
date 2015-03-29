#pragma once

#include "cocos2d.h"
#include "GameStructures.h"
#include <functional>

class DetailViewDataSource;
class GameBoardController;
class GameBoard;
class TetraminoViewController;

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
	GameBoard *_gameBoard;

	void fillDetailWithTetraminos(cocos2d::Node* aDetailView);
	cocos2d::Vec2 getPositionOnViewWithTetraminoOffset(GamePositionOnBoard aPosition);
	cocos2d::Node* getCurrentDetailTetraminoViewOnIndex(int aIndex);
	void setTetraminoLivesCountInViewForIndex(TetraminoViewController *aView, int aIndex);
	int getTetraminoTagForIndex(int aIndex);
	float getAnimationDurationWithFinalPosition(GamePositionOnBoard aFinalPosition);
	
	std::function<void(cocos2d::Node*)>  getAnimationEndCallbackWithFinalPosition(GamePositionOnBoard aFinalPosition);
	GamePositionOnBoard getPositionDifferenceWithFinalPosition(GamePositionOnBoard aFinalPosition);

};

