#include "GameHelper.h"
#include "stdlib.h"
#include "cocos2d.h"

using namespace std;
using namespace pugi;
using namespace cocos2d;

GameHelper::GameHelper(void)
{
}


GameHelper::~GameHelper(void)
{
}

int GameHelper::getRandomNumberFromUpInterval(int aUpInterval)
{
	int randomNumber = rand() % aUpInterval;
	return randomNumber;
}

xml_parse_result GameHelper::configFileForParsingWithKey(xml_document *aFile, string aKey)
{

	xml_parse_result result;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = aFile->load_file(aKey.c_str());
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	string fullPath = FileUtils::getInstance()->fullPathForFilename(aKey);
	unsigned char* pBuffer = NULL;
	ssize_t bufferSize = 0;
	const char *mode = "r";
	pBuffer = FileUtils::getInstance()->getFileData(fullPath.c_str(), mode, &bufferSize);
	result = aFile->load_buffer(pBuffer, bufferSize);
#endif

	return result;
}
