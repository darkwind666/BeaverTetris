#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

class GameBoardViewDataSource;
class TetraminoColorsDataSource;
class GameTimeStepController;

class GameBoardController : public cocos2d::Node
{
public:
	GameBoardController(void);
	~GameBoardController(void);

	void drawTetraminoTextureOnIndex(std::string aTetraminoTextureKey, int aTetraminoIndex);
	void cleanTetraminoOnIndex(int aTetraminoIndex);

	void redrawGameBoard();

private:

	GameBoardViewDataSource *_gameBoardViewDataSource;
	GameTimeStepController *_gameTimeStepController;
	std::vector<cocos2d::Sprite*> _tetraminosViews;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;

	void updateTetraminoViews();
	void updateGameBoardView();

	std::vector<cocos2d::Sprite*> getTetraminosViews();
	void addTetraminoViewsToController();
	void hideAllTetraminos();
	

};

