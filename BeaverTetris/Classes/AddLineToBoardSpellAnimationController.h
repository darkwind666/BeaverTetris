#pragma once

#include "cocos2d.h"
#include "AddLineToBoardBottomSpellDelegate.h"
#include <vector>
#include <functional>
#include "GameStructures.h"

class GameBoardController;
class AnimationSynchonizer;
class TetraminosAppearanceAnimationFactory;
class GameBoard;
class TetraminosInGameBoardViewDataSource;
class TetraminoColorsDataSource;

class AddLineToBoardSpellAnimationController : public AddLineToBoardBottomSpellDelegate, public cocos2d::Node
{
public:
	AddLineToBoardSpellAnimationController(GameBoardController *aGameBoardController, AnimationSynchonizer *aAnimationSynchonizer);
	~AddLineToBoardSpellAnimationController(void);

	virtual void upGameBoard();
	virtual void addLineToGameBoard();

private:

	AnimationSynchonizer *_animationSynchonizer;
	TetraminosAppearanceAnimationFactory *_tetraminosAppearanceAnimationFactory;
	GameBoard *_gameBoard;
	TetraminosInGameBoardViewDataSource *_tetraminosInGameBoardViewDataSource;
	GameBoardController *_gameBoardController;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;


	cocos2d::Node* getGameBoardView();
	void cleanAllTetraminosFromGameBoardView();
	void fillViewWithTetraminos(cocos2d::Node *aView);
	void addTetraminoOnViewForIndex(cocos2d::Node *aView, int aIndex);
	int getTetraminoViewTagForIndex(int aIndex);
	cocos2d::FiniteTimeAction* getAnimationWithGameBoardView(cocos2d::Node *aView);
	cocos2d::FiniteTimeAction* getMoveBoardAnimationWithView(cocos2d::Node *aView);
	std::function<void(Node*)> getAnimationEndCallback();
	void cleanBoardViewChildren(cocos2d::Node *aView);

	std::vector<GamePositionOnBoard> getBottomLinePositions();
	void setPositionWithIndexInCollection(int aWidthIndex, std::vector<GamePositionOnBoard> &aPositions);
	void addAnimationWithPositions(std::vector<GamePositionOnBoard> &aPositions);

};

