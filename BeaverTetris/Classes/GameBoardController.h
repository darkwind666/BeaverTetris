#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

class GameBoardViewDataSource;
class TetraminoColorsDataSource;

class GameBoardController : public cocos2d::Node
{
public:
	GameBoardController(void);
	~GameBoardController(void);

	void setRedrawAvailable(bool redrawAvailable);
	void drawTetraminoTextureOnIndex(std::string aTetraminoTextureKey, int aTetraminoIndex);
	void cleanTetraminoOnIndex(int aTetraminoIndex);

	void redrawGameBoard();

	bool getRedrawAvailable();

private:

	GameBoardViewDataSource *_gameBoardViewDataSource;
	bool _redrawAvailable;
	std::vector<cocos2d::Sprite*> _tetraminosViews;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;

	void updateTetraminoViews();
	void updateGameBoardView();

	std::vector<cocos2d::Sprite*> getTetraminosViews();
	void addTetraminoViewsToController();
	void hideAllTetraminos();
	

};

