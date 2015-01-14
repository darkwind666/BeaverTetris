#pragma once

#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class GameViewInformationFactory
{
public:
	GameViewInformationFactory(void);
	~GameViewInformationFactory(void);

	ViewElementInformation getViewInformationForKey(std::string aKey);

private:

	std::map <std::string , ViewElementInformation> _elementsInformation;

	void makeViewData();

	void makeLoadingScreenData();
	void makeStartGameSreenData();
	void makeSelectGameLevelScreenData();
	void makeMainGameScreenData();
	void makeRecordsScreenData();
	void makeDevelopersScreenData();

	cocos2d::Vec2 getScreenCenter();

};

