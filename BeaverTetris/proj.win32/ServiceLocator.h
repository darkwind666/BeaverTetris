#pragma once

class GameViewElementsDataSource;
class GameTransitionsController;

class ServiceLocator
{
public:

	static GameViewElementsDataSource* getGameViewElementsDataSource();
	static void setGameViewElementsDataSource(GameViewElementsDataSource *aGameViewElementsDataSource);

	static GameTransitionsController* getGameTransitionsController();
	static void setGameTransitionsController(GameTransitionsController *aGameTransitionsController);

};