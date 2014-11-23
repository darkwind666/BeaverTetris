#pragma once

#include <string>
#include "GameViewElementsDataSource.h"

class GameViewInformationFactory
{
public:
	GameViewInformationFactory(void);
	~GameViewInformationFactory(void);

	void setGameElementsInformationInDataSource(GameViewElementsDataSource aDataSource);

private:

	std::map <std::string , ViewElementInformation> _elementsInformation;

	std::map <std::string , ViewElementInformation> makeViewData(void);
	string GameViewInformationFactory::makeImageNameWithKey(const string gameElementKey);

};

