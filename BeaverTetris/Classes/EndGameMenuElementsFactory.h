#pragma once

#include "cocos2d.h"
#include <vector>

class EndGameMenuElementsCollectionCreator;

class EndGameMenuElementsFactory
{
public:
	EndGameMenuElementsFactory(void);
	~EndGameMenuElementsFactory(void);

	cocos2d::Node* getEndGameView();

private:

	EndGameMenuElementsCollectionCreator *_endGameMenuElementsCreator;

	void makePopUpBeaverOnView(cocos2d::Node *aView);
	void makePopUpMenuOnView(cocos2d::Node *aView);
	std::vector<cocos2d::Node*> getEndGameViewElements();
	cocos2d::Node* getEndGameBeaver();
	std::string getEndGameBeaverName();
	std::vector<cocos2d::Node*> getWinGameElements();
	std::string getEndGameViewName();
	
};

