#pragma once

#include <string>

class GameFileExtensionMaker
{
public:
	GameFileExtensionMaker(void);
	~GameFileExtensionMaker(void);

	static std::string getGraphicWithExtension(std::string aGraphicKey);
	static std::string* getGraphicsFilesWithExtension(std::string *aGraphicKey, int arraySize);

};

