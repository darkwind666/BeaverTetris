#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

class GameBoardViewDataSource;
class GameTimeStepController;
class TetraminoViewController;

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
	std::vector<TetraminoViewController*> _tetraminosViews;

	void updateTetraminoViews();
	void updateGameBoardView();

	std::vector<TetraminoViewController*> getTetraminosViews();
	void setLivesCountInTetraminoViewForIndex(TetraminoViewController* aTetraminoView, int aTetraminoIndex);
	void addTetraminoViewsToController();
	void hideAllTetraminos();

};

