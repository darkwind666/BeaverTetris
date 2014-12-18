#pragma once

#include <string>
#include "GameStructures.h"

class GameKeyWithSuffixSupporter
{
public:
	GameKeyWithSuffixSupporter(void);
	~GameKeyWithSuffixSupporter(void);

	static std::string makeSelectedImageForKey(std::string aKey);
	static std::string makeUnselectedImageForKey(std::string aKey);
	static void passImagesToMenuItemInformationWithKey(MenuItemInformation &aMenuItemInformation, std::string aKey);

};

