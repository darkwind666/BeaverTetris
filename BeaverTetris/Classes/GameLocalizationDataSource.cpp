#include "GameLocalizationDataSource.h"
#include "GameLocalizationKeys.h"
#include "cocos2d.h"

using namespace std;
using namespace pugi;
using namespace cocos2d;

GameLocalizationDataSource::GameLocalizationDataSource(void)
{
	_localizedStrings = getLocalizedStrings();
}

GameLocalizationDataSource::~GameLocalizationDataSource(void)
{
}

map<string, string> GameLocalizationDataSource::getLocalizedStrings()
{
	map<string, string> localizedStrings;
	xml_document localizationFile;
	xml_parse_result result;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = localizationFile.load_file(localizationFileNameKey.c_str());
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	string fullPath = FileUtils::getInstance()->fullPathForFilename(localizationFileNameKey);
	unsigned char* pBuffer = NULL;
	ssize_t bufferSize = 0;
	const char *mode = "r";
	pBuffer = FileUtils::getInstance()->getFileData(fullPath.c_str(), mode, &bufferSize);
	result = localizationFile.load_buffer(pBuffer, bufferSize);
#endif

	if (result)
	{
		xml_node localizations = localizationFile.child(localizationsKey.c_str());
		xml_node localizationString;
		for (localizationString = localizations.first_child(); localizationString; localizationString = localizationString.next_sibling())
		{
			string localizedString = getLocalizedStringFromNode(localizationString);
			string key = localizationString.attribute(localizationTypeKey.c_str()).as_string();
			localizedStrings[key] = localizedString;
		}
	}
	return localizedStrings;
}

string GameLocalizationDataSource::getLocalizedStringFromNode(xml_node &node)
{
	string currentSystemLanguage = getCurrentSystemLanguage();
	string localizedString = node.attribute(currentSystemLanguage.c_str()).as_string();
	return localizedString;
}

string GameLocalizationDataSource::getCurrentSystemLanguage()
{
	string currentSystemLanguage = localizationEnglishLanguageKey;
	cocos2d::LanguageType language = cocos2d::Application::sharedApplication()->getCurrentLanguage();
	if (language == cocos2d::LanguageType::RUSSIAN)
	{
		currentSystemLanguage = localizationRussianLanguageKey;
	}
	return currentSystemLanguage;
}

string GameLocalizationDataSource::getLocalizedStringForKey(string aKey)
{
	return _localizedStrings[aKey];
	//string a = string("a");
	//return a;
}
