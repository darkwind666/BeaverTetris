#pragma once

#include <string>
#include "GameViewElementsDataSource.h"

class GameViewInformationFactory
{
public:
	GameViewInformationFactory(void);
	~GameViewInformationFactory(void);

	ViewElementInformation getViewInformationForKey(std::string aKey);

private:

	std::map <std::string , ViewElementInformation> _elementsInformation;

	std::map <std::string , ViewElementInformation> makeViewData(void);

};

