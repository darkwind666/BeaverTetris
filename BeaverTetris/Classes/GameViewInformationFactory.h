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
	void makeStartGameMenuItemsData();
	void makeStartGameRegulateSoundPopUpData();
	void makeSelectGameLevelScreenData();
	void makeSelectGameLevelMenuData();
	void makeSelectGameLevelPlayerStatusData();
	void makeSelectGameLevelPlayerCreatorControllerData();
	void makeMainGameScreenData();
	void makeMainGameWorldData();
	void makeMainGameHudsData();
	void makeMainGamePlayerControllersData();
	void makeMainGamePlayerScoreControllersData();
	void makeMainGameVictoryConditionData();
	void makeMainGameSpellsIconsData();
	void makeRemoveCurrentDetailSpellData();
	void makeMainGamePausePopUpData();
	void makeMainGameEndPopUpData();
	void makeRecordsScreenData();
	void makeGameRecordsAnimationData();
	void makeDevelopersScreenData();
	void makeGameDevelopersAnimationData();
	void makeGameDevelopersBoardData();

	cocos2d::Vec2 getScreenCenter();
	float getScreenCenterX();
	float getScreenCenterY();
	std::string getImageNameForKey(std::string aKey);

};

