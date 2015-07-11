#pragma once

#include "pugixml.hpp"
#include <string>

class GameHelper
{
public:
	GameHelper(void);
	~GameHelper(void);

	static int getRandomNumberFromUpInterval(int aUpInterval);
	static pugi::xml_parse_result configFileForParsingWithKey(pugi::xml_document *aFile, std::string aKey);
};

