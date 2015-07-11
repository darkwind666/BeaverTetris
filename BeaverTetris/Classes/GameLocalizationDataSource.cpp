#include "GameLocalizationDataSource.h"
#include "GameLocalizationKeys.h"
#include "GameHelper.h"
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
	xml_parse_result result = GameHelper::configFileForParsingWithKey(&localizationFile, localizationFileNameKey);

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
}
