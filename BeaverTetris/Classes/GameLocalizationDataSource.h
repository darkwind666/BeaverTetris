#pragma once

#include "ServiceInterface.h"
#include "pugixml.hpp"
#include <string>
#include <map>

class GameLocalizationDataSource : public ServiceInterface
{
public:
	GameLocalizationDataSource(void);
	~GameLocalizationDataSource(void);

	std::string getLocalizedStringForKey(std::string aKey);

private:

	std::map<std::string, std::string> _localizedStrings;

	std::map<std::string, std::string> getLocalizedStrings();
	std::string getLocalizedStringFromNode(pugi::xml_node &node);
	std::string getCurrentSystemLanguage();

};

