#include "StringsSupporter.h"
#include <sstream>
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameLocalizationDataSource.h"

using namespace std;

StringsSupporter::StringsSupporter(void)
{
}


StringsSupporter::~StringsSupporter(void)
{
}

string StringsSupporter::getStringFromNumber(int aNumber)
{
	stringstream str;
	str << aNumber;
	string numberInString = str.str();
	return numberInString;
}

string StringsSupporter::getLocalizedStringFromKey(string aKey)
{
	GameLocalizationDataSource *gameLocalizationDataSource = (GameLocalizationDataSource*)ServiceLocator::getServiceForKey(gameLocalizationDataSourceKey);
	string localizedText = gameLocalizationDataSource->getLocalizedStringForKey(aKey);
	return localizedText;
}