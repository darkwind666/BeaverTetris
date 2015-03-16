#pragma once

#include <string>

class GameKeyWithSuffixSupporter
{
public:
	GameKeyWithSuffixSupporter(void);
	~GameKeyWithSuffixSupporter(void);

	static std::string makeSelectedImageForKey(std::string aKey);
	static std::string makeUnselectedImageForKey(std::string aKey);
	static std::string makeLockedImageForKey(std::string aKey);

};

