#pragma once

#include <string>

class StringsSupporter
{
public:
	StringsSupporter(void);
	~StringsSupporter(void);

	static std::string getStringFromNumber(int aNumber);
	static std::string getLocalizedStringFromKey(std::string aKey);

};

